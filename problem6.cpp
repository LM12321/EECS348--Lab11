/*
Name of Program: problem6.cpp
Author: Logan Whitt
KUID: 3152587

Description: takes in two column indexes and swaps them
Output: given matricies and new swapped matricies

Collaborators: https://www.geeksforgeeks.org/cpp/operator-overloading-cpp/
for overloading and learning about this-> interactions

Creation Date: 11/11/25 - 11/13/25
*/


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Matrix{
    

    public:
        vector<vector<int>> rows;
        int size_of_matrix;

        void print_matrix(){
            for (vector<int> row: this->rows){
                for (int element: row){
                    cout << '\t' << element << " ";
                }
                cout << endl;
            }
        }
        void append_row_to_matrix(vector<int> row){
            this->rows.push_back(row);
        }
        void change_matrix_size(int new_matrix_size){
            this->size_of_matrix = new_matrix_size;
        }
        
        Matrix transpose_matrix(){
            Matrix transposed_matrix;   //initalize transposed matrix
            transposed_matrix.size_of_matrix = this->size_of_matrix;    //intialize size of matrix
            for (int i = 0; i < this->size_of_matrix; i++){   //iterate through rows
                vector<int> column;
                for (int j = 0; j < this->size_of_matrix; j++){   //iterate through columns
                    column.push_back(this->rows[j][i]); //append column elements
                }
                transposed_matrix.rows.push_back(column); //append the column of the original matrix to the transposed version of it
                
            }
            return transposed_matrix;   //return transposed matrix
        }

        Matrix operator+(Matrix& other_matrix){
            Matrix result;  //initalize result matrix
            result.size_of_matrix = this->size_of_matrix;   //intialize size of matrix
            for (int i = 0; i < this->size_of_matrix; i++){   //iterate through rows
                vector<int> temp_row;   //initalize temp row
                for (int j = 0; j < this->size_of_matrix; j++){   //iterate through columns
                    temp_row.push_back(this->rows[i][j] + other_matrix.rows[i][j]);   //add addition between this matrix at [i][j] + other matrix at [i][j]
                }
                result.rows.push_back(temp_row);    //add row to resulting matrix rows
            }
            return result;  //return result
        }

        int multiply_rows(vector<int>& row_one, vector<int>& row_two, int n){
            int result = 0; //initalize the result
            for(int i = 0; i < n; i++){
                result += row_one[i] * row_two[i];  //add elements at row one and two multiplied to each other to the result
            }
            return result;  //return the result
        }

        Matrix operator*(Matrix& other_matrix){
            
            Matrix transposed_other_matrix = other_matrix.transpose_matrix(); //get transposed other matrix
            Matrix multiplication_result;  //initalize result matrix
            multiplication_result.size_of_matrix = this->size_of_matrix;    //assign multiplication result size of matrix
            
            for (int i = 0; i < this->size_of_matrix; i++){   //iterate through rows
                vector<int> temp_row;   //initalize temp row
                for (int j = 0; j < this->size_of_matrix; j++){   //iterate through columns
                    int element = multiply_rows(this->rows[i], transposed_other_matrix.rows[j], this->size_of_matrix);  //get element of multiplication
                    temp_row.push_back(element);   //add addition between this matrix at [i][j] + other matrix at [i][j]
                }
                multiplication_result.rows.push_back(temp_row);    //add row to resulting matrix rows
            }
            return multiplication_result;  //return result
        }
        int return_main_diagonal(){
            int diagonal = 0;   //get diagonal
            for (int i = 0; i < this->size_of_matrix; i++){ //iterate through the size of the matrix
                diagonal += this->rows[i][i];   //add
            }
            return diagonal;    
        }

        int return_anti_diagonal(){
            int n = this->size_of_matrix;   //get size of matrix
            int anti_diagonal = 0; //initalize anti diagonal
            for (size_t i = 0; i < n; i++){
                anti_diagonal += this->rows[i][n - i - 1];
                //i is the row
                // n - i - 1 is the position of the anti diagonal
                // it isn't just n - i as that would be out of range if i = 0
            }
            return anti_diagonal;   //return the anti diagonal
        }

        int return_matrix_diagonals(){
            int diagonals = 0;
            diagonals += this->return_main_diagonal();
            diagonals += this->return_anti_diagonal();
            return diagonals;
        }   
        Matrix create_and_return_copy(){
            Matrix matrix_copy;  //initalize matrix copy
            for (int i = 0; i < this->size_of_matrix; i++){
                matrix_copy.rows.push_back(this->rows[i]); //add rows to matrix copy
            }

            return matrix_copy; //return matrix copy
        }

        
};

Matrix swap_columns_of_matrix(Matrix matrix, int original_column = 0, int ending_column = 1){

    if (original_column < 0 || original_column >= matrix.size_of_matrix){ //if the given original row is out of range
        cout << "Invalid original row index given." << endl;
        return matrix;
    }
    if (ending_column < 0 || ending_column >= matrix.size_of_matrix){ //if the given ending row is out of range
        cout << "Invalid ending row index given." << endl;
        return matrix;
    }

    matrix = matrix.transpose_matrix();     //convert the columns into rows
    

    vector<int> old_column = matrix.rows[original_column];    //get old row
    vector<int> swap_column = matrix.rows[ending_column];     // get swap row
    matrix.rows[original_column] = swap_column;   //make the original row  the swap row
    matrix.rows[ending_column] = old_column; //make the ending row the old row

    matrix = matrix.transpose_matrix(); //return the matrix to what it was

    return matrix;  //return the matrix
}

Matrix swap_rows_of_matrix(Matrix matrix, int original_row = 0, int ending_row = 1){

    if (original_row < 0 || original_row >= matrix.size_of_matrix){ //if the given original row is out of range
        cout << "Invalid original row index given." << endl;
        return matrix;
    }
    if (ending_row < 0 || ending_row >= matrix.size_of_matrix){ //if the given ending row is out of range
        cout << "Invalid ending row index given." << endl;
        return matrix;
    }

    vector<int> old_row = matrix.rows[original_row];    //get old row
    vector<int> swap_row = matrix.rows[ending_row];     // get swap row
    matrix.rows[original_row] = swap_row;   //make the original row  the swap row
    matrix.rows[ending_row] = old_row; //make the ending row the old row

    return matrix;  //return the matrix
}




std::vector<std::string> split_string_into_vector_with_delimiter(std::string line, std::string delimiter){
    //from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    
    std::vector<std::string> tokens; //initalize vector of tokens
    size_t position = 0; //initalize position
    std::string token;  //initalize token string
    while ((position = line.find(delimiter)) != std::string::npos) { //while there are still things to split
        token = line.substr(0, position);   //get token 
        tokens.push_back(token);    //push back
        line.erase(0, position + delimiter.length());   //erase part that was split
    }
    
    if (!(line.empty()) && !(line == "\r")){
        tokens.push_back(line); //add think to tokens
    }
    
    return tokens;  //return tokens
}
vector<int> convert_row_strings_to_row_ints(vector<string> row_strings){
    vector<int> row_ints;
    int n = row_strings.size();
    row_ints.resize(n);

    for (int i = 0; i < n; i++){
        int int_element = stoi(row_strings[i]);
        row_ints[i] = int_element;
    }

    return row_ints;
}


vector<Matrix> read_file_and_return_vector_of_matricies(std::string& filepath){
    std::string line;   //initalize line string
    std::ifstream myfile (filepath);    //initalize file

    if (!myfile){
        cout << "File not found" << endl;   //tell the user that we couldn't read the file
        exit(EXIT_FAILURE); //end program
    }

    int line_counter = 0;   //initalize line_counter
    int matrix_size = 0;    //initalize matrix size
    Matrix matrix_one;  //initalize matrix_one
    Matrix matrix_two;  //intitalize matrix_two
    
    if (myfile.is_open()){  //if the file is open

        while (getline (myfile, line)){ //while there are lines in file

            if (line.empty() || line == "\r"){  //ignore empty line
                continue;   //continue iteration as if nothing happened
            }

            if (line_counter == 0){
                cout << "Initalize size of matricies:" << endl;
                matrix_size = stoi(line);   //convert the string to an int
                cout << matrix_size << endl;    //print out the matrix size

                if (matrix_size <= 1){   //if the matrix size is invalid, raise error
                    cout << "Error -- matrix size is not valid" << endl;    //tell user
                    cout << matrix_size << endl;    //print out the matrix size
                    exit(EXIT_FAILURE); //end program
                }
                matrix_one.change_matrix_size(matrix_size);
                matrix_two.change_matrix_size(matrix_size);
                line_counter++; // increment the line counter by 1
                continue;   //continue iteration

            }else{

                vector<string> matrix_row_strings = split_string_into_vector_with_delimiter(line, " "); //split the given line by " "

                if (matrix_row_strings.size() != matrix_size){  //if the size of the row is not valid
                    cout << "Error -- matrix size is not valid" << endl;    //tell user
                    cout << matrix_row_strings.size() << endl;      //show size it was
                    exit(EXIT_FAILURE); //end program
                }

                vector<int> matrix_row_ints = convert_row_strings_to_row_ints(matrix_row_strings);  //get row of ints

                if (line_counter < matrix_size + 1){    //still on matrix 1; add inputs to matrix 1
                    matrix_one.append_row_to_matrix(matrix_row_ints);   //add row of ints to matrix 1

                }else{   //add inputs to matrix two
                    matrix_two.append_row_to_matrix(matrix_row_ints);   //add row of ints to matrix 2
                }
            }
            line_counter++; // increment the line counter by 1
        }
    }
    myfile.close(); //close the file
    vector<Matrix> matricies = {matrix_one, matrix_two};

    return matricies;
}

int main(){
    string filepath;
    cout << "Input file name/path here:" << endl; 
    cin >> filepath;
    
    vector<Matrix> matricies = read_file_and_return_vector_of_matricies(filepath);  //read file
    cout << "Matrix 1:" << endl;    //print the header of matrix one
    matricies[0].print_matrix();    //print matrix one
    cout << "Matrix 2:" << endl;    //print the header of matrix two
    matricies[1].print_matrix();    //print matrix two
    cout << "Matrix 1 Columns Swapped:" << endl;
    Matrix swapped_matrix_one = swap_columns_of_matrix(matricies[0]);
    swapped_matrix_one.print_matrix();

}