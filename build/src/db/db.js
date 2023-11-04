"use strict";
var __values = (this && this.__values) || function(o) {
    var s = typeof Symbol === "function" && Symbol.iterator, m = s && o[s], i = 0;
    if (m) return m.call(o);
    if (o && typeof o.length === "number") return {
        next: function () {
            if (o && i >= o.length) o = void 0;
            return { value: o && o[i++], done: !o };
        }
    };
    throw new TypeError(s ? "Object is not iterable." : "Symbol.iterator is not defined.");
};
var __read = (this && this.__read) || function (o, n) {
    var m = typeof Symbol === "function" && o[Symbol.iterator];
    if (!m) return o;
    var i = m.call(o), r, ar = [], e;
    try {
        while ((n === void 0 || n-- > 0) && !(r = i.next()).done) ar.push(r.value);
    }
    catch (error) { e = { error: error }; }
    finally {
        try {
            if (r && !r.done && (m = i["return"])) m.call(i);
        }
        finally { if (e) throw e.error; }
    }
    return ar;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.deleteData = exports.registerData = exports.createTable = exports.callback = void 0;
var sqlite3 = require("sqlite3");
// Callback function to display query results
function callback(NotUsed, argc, argv, azColName) {
    for (var i = 0; i < argc; i++) {
        console.log(azColName[i] + ': ' + (argv[i] ? argv[i] : 'NULL'));
    }
    return 0;
}
exports.callback = callback;
// Function to create a table in the database
function createTable(db) {
    // SQL statement to create 'Data' table with ID, Name, Age, and Occupation columns
    var createTableSQL = 'CREATE TABLE IF NOT EXISTS Data (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Age INT NOT NULL, Occupation TEXT);';
    db.run(createTableSQL, function (err) {
        if (err) {
            console.error('Error creating table: ' + err.message);
        }
        else {
            console.log('Table created successfully.');
        }
    });
}
exports.createTable = createTable;
// Function to register data in the 'Data' table dynamically
function registerData(columnData) {
    var e_1, _a;
    var db = new sqlite3.Database('database.db');
    // Create the 'Data' table if it does not exist
    createTable(db);
    // Dynamically construct SQL query based on column names provided in 'columnData' map
    var columns = '';
    var placeholders = '';
    try {
        for (var columnData_1 = __values(columnData), columnData_1_1 = columnData_1.next(); !columnData_1_1.done; columnData_1_1 = columnData_1.next()) {
            var _b = __read(columnData_1_1.value, 2), key = _b[0], value = _b[1];
            columns += key + ', ';
            placeholders += '?, ';
        }
    }
    catch (e_1_1) { e_1 = { error: e_1_1 }; }
    finally {
        try {
            if (columnData_1_1 && !columnData_1_1.done && (_a = columnData_1.return)) _a.call(columnData_1);
        }
        finally { if (e_1) throw e_1.error; }
    }
    // Remove the trailing comma and space in 'columns' and 'placeholders' strings
    columns = columns.slice(0, -2);
    placeholders = placeholders.slice(0, -2);
    // Construct the SQL query for inserting data
    var sql = "INSERT INTO Data (".concat(columns, ") VALUES (").concat(placeholders, ")");
    db.run(sql, Array.from(columnData.values()), function (err) {
        if (err) {
            console.error('Error inserting data: ' + err.message);
        }
        else {
            console.log('Data inserted successfully.');
        }
    });
    // Close the database connection
    db.close();
}
exports.registerData = registerData;
function deleteData(ID) {
    var db = new sqlite3.Database('database.db');
    var sql = 'DELETE FROM Data WHERE ID = ?';
    db.run(sql, ID, function (err) {
        if (err) {
            console.error('Error deleting data: ' + err.message);
        }
        else {
            console.log('Data deleted successfully.');
        }
    });
    // Close the database connection
    db.close();
}
exports.deleteData = deleteData;
