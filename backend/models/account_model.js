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
      'insert into account (fname, lname, owner) values (?, ?, ?)',
      [account.fname, account.lname, account.owner],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where account_number=?', [id], callback);
  },
  update: function(id, amount, callback) {
    console.log("account update function");
    return db.query('update account set balance = balance + ? where account_number=?', [amount, id], callback);
  }
};

module.exports = account;
