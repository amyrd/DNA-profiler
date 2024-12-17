# DNA Profiling Application

## Overview  
This program analyzes DNA sequences to match individuals based on their Short Tandem Repeats (STRs). It allows users to load a database of STR counts, load a DNA sequence, process it to find STR matches, search for individuals, and use a custom "find" function to locate specific sequences in the DNA.

---

## Features  
1. **Load Database**  
   - **Command:** `load_db <filename>`  
   - Loads a database file containing individuals' STR counts.

2. **Display Data**  
   - **Command:** `display`  
   - Displays loaded database, DNA sequence, and processed STR counts.

3. **Load DNA Sequence**  
   - **Command:** `load_dna <filename>`  
   - Loads a DNA sequence from a file.

4. **Process DNA**  
   - **Command:** `process`  
   - Analyzes the loaded DNA sequence to find STR counts.

5. **Search Database**  
   - **Command:** `search`  
   - Searches for a match between the processed DNA STR counts and individuals in the database.

6. **Find Sequence (Creative Component)**  
   - **Command:** `find`  
   - Prompts the user to input a specific sequence and a marker to highlight the start and end of the sequence in the DNA.

7. **Exit Program**  
   - **Command:** `#`  

---

## Usage  
1. **Load a Database**  
   ```
   Enter command: load_db <filename>
   ```

2. **Load a DNA Sequence**  
   ```
   Enter command: load_dna <filename>
   ```

3. **Process DNA**  
   ```
   Enter command: process
   ```

4. **Search Database**  
   ```
   Enter command: search
   ```

5. **Find a Sequence**  
   ```
   Enter command: find
   ```

6. **Display Current Data**  
   ```
   Enter command: display
   ```

7. **Exit the Program**  
   ```
   Enter command: #
   ```

---

## Example Workflow  
1. Load database: `load_db database.txt`  
2. Load DNA: `load_dna sequence.txt`  
3. Process DNA: `process`  
4. Search for matches: `search`  
5. Find a custom sequence: `find`  

---

## Notes  
- Ensure the database and DNA files exist and follow the correct format.  
- Use `display` to check loaded data and STR counts at any time.  
- The `find` function allows you to locate and mark specific DNA sequences dynamically.
- this description was created using CHATGPT

---

## Author  
**Amyr Dayrit**
