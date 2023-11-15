const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'bankuser',
  password: 'bankpass',
  database: 'banksimul'
});
module.exports = connection;