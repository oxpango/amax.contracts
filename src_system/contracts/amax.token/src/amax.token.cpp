#include <amax.token/amax.token.hpp>

namespace eosio {

void token::create( const name&   issuer,
                    const asset&  maximum_supply )
{
    require_auth( get_self() );

    check(is_account(issuer), "issuer account does not exist");
    auto sym = maximum_supply.symbol;
    check( sym.is_valid(), "invalid symbol name" );
    check( maximum_supply.is_valid(), "invalid supply");
    check( maximum_supply.amount > 0, "max-supply must be positive");

    stats statstable( get_self(), sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing == statstable.end(), "token with symbol already exists" );

    statstable.emplace( get_self(), [&]( auto& s ) {
       s.supply.symbol = maximum_supply.symbol;
       s.max_supply    = maximum_supply;
       s.issuer        = issuer;
    });
}


void token::issue( const name& issuer, const asset& quantity, const string& memo )
{
    auto sym = quantity.symbol;
    check( sym.is_valid(), "invalid symbol name" );
    check( memo.size() <= 256, "memo has more than 256 bytes" );

    stats statstable( get_self(), sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
    const auto& st = *existing;
    check( issuer == st.issuer, "tokens can only be issued to issuer account" );

    require_auth( st.issuer );
    check( quantity.is_valid(), "invalid quantity" );
    check( quantity.amount > 0, "must issue positive quantity" );

    check( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    check( quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.supply += quantity;
    });

    add_balance( st.issuer, quantity, st.issuer );
}

void token::setissue( const name& issuer, const symbol& sym, const name& newissuer )
{
    check( issuer != newissuer, "tokens issuer account is same" );

    check( sym.is_valid(), "invalid symbol name" );
    stats statstable( get_self(), sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
    const auto& st = *existing;
    check( issuer == st.issuer, "tokens can only be issued to issuer account" );

    require_auth( st.issuer );
    check( sym == st.supply.symbol, "symbol precision mismatch" );

    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.issuer = newissuer;
    });
}

void token::slashblack( const name& target, const asset& quantity, const string& memo ){
   check( has_auth("amax"_n) || has_auth("armoniaadmin"_n), "no auth to operate" );

   check( _is_blacklisted(target, _self), "blacklisted acccounts only!" );

   auto sym = quantity.symbol;
   check( memo.size() <= 256, "memo has more than 256 bytes" );
   check( quantity.is_valid(), "invalid quantity" );
   check( quantity.amount > 0, "must slash positive quantity" );

   // sub_balance( target, quantity );
   accounts from_acnts( get_self(), target.value );
   const auto& from = from_acnts.get( quantity.symbol.code().raw(), "no balance object found" );
   check( from.balance >= quantity, "overdrawn balance" );
   from_acnts.modify( from, same_payer, [&]( auto& a ) {
      a.balance -= quantity;
   });


   stats statstable( get_self(), sym.code().raw() );
   auto existing = statstable.find( sym.code().raw() );
   check( existing != statstable.end(), "token with symbol does not exist" );
   const auto& st = *existing;

   statstable.modify( st, same_payer, [&]( auto& s ) {
      s.supply -= quantity;
   });

   require_recipient( target );
}

void token::retire( const asset& quantity, const string& memo )
{
    auto sym = quantity.symbol;
    check( sym.is_valid(), "invalid symbol name" );
    check( memo.size() <= 256, "memo has more than 256 bytes" );

    stats statstable( get_self(), sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing != statstable.end(), "token with symbol does not exist" );
    const auto& st = *existing;

    require_auth( st.issuer );
    check( quantity.is_valid(), "invalid quantity" );
    check( quantity.amount > 0, "must retire positive quantity" );

    check( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );

    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.supply -= quantity;
    });

    sub_balance( st.issuer, quantity );
}

void token::blacklist( const std::vector<name>& targets, const bool& to_add ){
   check( has_auth( _self ) || has_auth( "armoniaadmin"_n ), "not authorized" );
   check( targets.size() <= 50, "overiszed targets: " + std::to_string( targets.size()) );

   blackaccounts black_accts( _self, _self.value );
   if (to_add) {
      for (auto& target : targets) {
         if (black_accts.find( target.value ) != black_accts.end())
            continue;   //found and skip

         black_accts.emplace( _self, [&]( auto& a ){
            a.account = target;
         });
      }
      
   } else { //to remove
      for (auto& target : targets) {
         auto itr = black_accts.find( target.value );
         if ( itr == black_accts.end())
            continue;   //not found and skip

         black_accts.erase( itr );
      }
   }
}

void token::transfer( const name&    from,
                      const name&    to,
                      const asset&   quantity,
                      const string&  memo )
{
   require_auth( from );

   check( from != to, "cannot transfer to self" );
   check( is_account( to ), "to account does not exist");

   if ( from == "aaaaaaaaaaaa"_n )
      check( to == "amax"_n, "can only transfer to amax" );

   if (_is_blacklisted(from, "amax.token"_n)) {
      check( to == "oooo"_n, "blacklisted accounts can only transfer to oooo" );
   }

   auto sym = quantity.symbol.code();
   stats statstable( get_self(), sym.raw() );
   const auto& st = statstable.get( sym.raw() );

   require_recipient( from );
   require_recipient( to );

   check( quantity.is_valid(), "invalid quantity" );
   check( quantity.amount > 0, "must transfer positive quantity" );
   check( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
   check( memo.size() <= 256, "memo has more than 256 bytes" );

   auto payer = has_auth( to ) ? to : from;

   sub_balance( from, quantity );
   add_balance( to, quantity, payer );
}

void token::sub_balance( const name& owner, const asset& value ) {
   accounts from_acnts( get_self(), owner.value );

   const auto& from = from_acnts.get( value.symbol.code().raw(), "no balance object found" );
   check( from.balance.amount >= value.amount, "overdrawn balance" );

   from_acnts.modify( from, owner, [&]( auto& a ) {
      a.balance -= value;
   });
}

void token::add_balance( const name& owner, const asset& value, const name& ram_payer )
{
   accounts to_acnts( get_self(), owner.value );
   auto to = to_acnts.find( value.symbol.code().raw() );
   if( to == to_acnts.end() ) {
      to_acnts.emplace( ram_payer, [&]( auto& a ){
        a.balance = value;
      });
   } else {
      to_acnts.modify( to, same_payer, [&]( auto& a ) {
        a.balance += value;
      });
   }
}

void token::open( const name& owner, const symbol& symbol, const name& ram_payer )
{
   require_auth( ram_payer );

   check( is_account( owner ), "owner account does not exist" );

   auto sym_code_raw = symbol.code().raw();
   stats statstable( get_self(), sym_code_raw );
   const auto& st = statstable.get( sym_code_raw, "symbol does not exist" );
   check( st.supply.symbol == symbol, "symbol precision mismatch" );

   accounts acnts( get_self(), owner.value );
   auto it = acnts.find( sym_code_raw );
   if( it == acnts.end() ) {
      acnts.emplace( ram_payer, [&]( auto& a ){
        a.balance = asset{0, symbol};
      });
   }
}

void token::close( const name& owner, const symbol& symbol )
{
   require_auth( owner );
   accounts acnts( get_self(), owner.value );
   auto it = acnts.find( symbol.code().raw() );
   check( it != acnts.end(), "Balance row already deleted or never existed. Action won't have any effect." );
   check( it->balance.amount == 0, "Cannot close because the balance is not zero." );
   acnts.erase( it );
}

} /// namespace eosio
