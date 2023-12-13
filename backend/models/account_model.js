const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where account_number=?', [id], callback);
  },
  add: function(account, callback) {
    return db.query(
      'insert into account (account_number, balance, owner, credit) values (?, ?, ?, ?)',
      [account.account_number, account.balance, account.owner, account.credit],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where account_number=?', [id], callback);
  },
  update: function(id, account, callback) {
    console.log("account update function");
    return db.query(
      'update account set balance = ?, owner = ?, credit = ? where account_number=?',
      [account.balance, account.owner, account.credit, id],
      callback
    );
  },
  patch: function(id, account, callback) {
    console.log("account patch function");
    return db.query(
      'update account set balance=balance + ? where account_number=?',
      [account.balance, id],
      callback
    );
  }
};

module.exports = account;
