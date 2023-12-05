const db = require('../database');

const login={
  checkPassword: function(username, callback) {
      return db.query('SELECT card_pin FROM card WHERE card_id = ?',[username], callback); 
    }
};
          
module.exports = login;