const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const card={
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from card where card_id=?', [id], callback);
  },
  add: function(card, callback) {
    bcrypt.hash(card.card_pin, saltRounds, function(err, hash) {
      return db.query('insert into card (card_id, card_owner, card_account, card_pin) values(?,?,?,?)',
      [card.card_id, card.card_owner, card.card_account, hash], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from card where card_id=?', [id], callback);
  },
  update: function(id, card, callback) {
    bcrypt.hash(card.card_pin, saltRounds, function(err, hash) {
      return db.query('update card set card_owner=?, card_account=?, card_pin=? where card_id=?',
      [card.card_owner, card.card_account, hash, id], callback);
    });
  }

}

module.exports = card;