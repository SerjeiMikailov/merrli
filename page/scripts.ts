import * as sqlite3 from 'sqlite3';

import { createTable, registerData, deleteData } from '../src/db/db'; 

const db: sqlite3.Database = new sqlite3.Database('database.db');

createTable(db);

const columnData: Map<string, string> = new Map();
columnData.set("Name", "John Doe");
columnData.set("Age", "30");
columnData.set("Occupation", "Engineer");

registerData(columnData);

db.close();
