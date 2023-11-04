import * as sqlite3 from 'sqlite3';

// Callback function to display query results
export function callback(this: any, NotUsed: any, argc: number, argv: string[], azColName: string[]): number {
    for (let i = 0; i < argc; i++) {
        console.log(azColName[i] + ': ' + (argv[i] ? argv[i] : 'NULL'));
    }
    return 0;
}

// Function to create a table in the database
export function createTable(db: sqlite3.Database): void {
    // SQL statement to create 'Data' table with ID, Name, Age, and Occupation columns
    const createTableSQL: string = 'CREATE TABLE IF NOT EXISTS Data (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Age INT NOT NULL, Occupation TEXT);';

    db.run(createTableSQL, function(err) {
        if (err) {
            console.error('Error creating table: ' + err.message);
        } else {
            console.log('Table created successfully.');
        }
    });
}

// Function to register data in the 'Data' table dynamically
export function registerData(columnData: Map<string, string>): void {
    const db = new sqlite3.Database('database.db');
    // Create the 'Data' table if it does not exist
    createTable(db);

    // Dynamically construct SQL query based on column names provided in 'columnData' map
    let columns: string = '';
    let placeholders: string = '';
    for (const [key, value] of columnData) {
        columns += key + ', ';
        placeholders += '?, ';
    }
    // Remove the trailing comma and space in 'columns' and 'placeholders' strings
    columns = columns.slice(0, -2);
    placeholders = placeholders.slice(0, -2);

    // Construct the SQL query for inserting data
    const sql: string = `INSERT INTO Data (${columns}) VALUES (${placeholders})`;

    db.run(sql, Array.from(columnData.values()), function(err) {
        if (err) {
            console.error('Error inserting data: ' + err.message);
        } else {
            console.log('Data inserted successfully.');
        }
    });

    // Close the database connection
    db.close();
}

export function deleteData(ID: number): void {
    const db = new sqlite3.Database('database.db');

    const sql: string = 'DELETE FROM Data WHERE ID = ?';

    db.run(sql, ID, function(err) {
        if (err) {
            console.error('Error deleting data: ' + err.message);
        } else {
            console.log('Data deleted successfully.');
        }
    });

    // Close the database connection
    db.close();
}
