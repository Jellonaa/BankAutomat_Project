const db = require('../database');

const customer = {
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from customer where customer_id=?', [id], callback);
  },
  add: function(customer, callback) {
    return db.query(
      'insert into customer (fname,lname) values(?,?)',
      [customer.fname, customer.lname],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where customer_id=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set fname=?,lname=? where customer_id=?',
      [customer.fname, customer.lname, id],
      callback
    );
  }
};
module.exports = customer;