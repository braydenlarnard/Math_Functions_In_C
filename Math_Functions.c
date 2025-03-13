#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Computes and returns the values of slope point form using the given values
double * linear_func(int a, int b, const double * values, int size) {
	double* ptrY = (double*) malloc(size * sizeof(double)); // Variable representing the resulting value
	// For loop that computes the y value for each double in the array
	for (int i = 0; i  < size; i++) {
		ptrY[i] = a * values[i] + b;
	}
	return ptrY; // Returns the pointer to the resulting values
}


// Computes and returns the value of a quadriatic function using the given values
double * quadratic_func(int a, int b, const double * values, int size) {
	double* ptrY = (double*) malloc(size * sizeof(double)); //Variable representing a pointer to the y value
	// For loop that computes the y value for each double in the array
	for (int i = 0; i < size; i++) {
		ptrY[i] = (values[i] * values[i]) + (a * values[i]) + b;
	}
	return ptrY; // Returns the pointer to the array of resulting values
}


// Computes and returns the values of an exponential function using the given values
double * exp_func(int a, int b, const double * values, int size) {
	double* ptrY = (double*) malloc(size * sizeof(double)); //Variable representing a pointer to the y values
	// For loop that computes the y value for each double in the array
	for (int i = 0; i < size; i++) {
		ptrY[i] = exp(a * values[i]);
	}
	return ptrY; // Returns the pointer to the array of resulting values
}


// Computes and returns the values of a sin functinon using the given values
double * sin_func(int a, int b, const double * values, int size) {
	double* ptrY = (double*) malloc(size * sizeof(double)); //Variable representng a pointer to the y values
	// For loop that computes the y value for each double in the array
	for (int i = 0; i < size; i++) {
		ptrY[i] = a * sin(b * values[i]);
	}
	return ptrY; // Returns the pointer to the array of resulting values
}

// Uses other functions to calculate the derivatives based on input
double * func_derivative(const char * func, double * val_plus, double * val, double * val_minus, int a, int b, int order, double h, int size) {
	double* ptrY = (double*) malloc(size * sizeof(double)); // Varibale representing a pointer to the y values

	// For loop that assigns a value to each element in the array
	for (int i = 0; i < size; i++) {
		// switch statement that switches between the 0th, 1st, or 2nd order derivative of the specified function
		switch (order) {
		case 0:
			// If/else statements that determine what function to use based on the first char of the string inputted
			if (func[0] == 's') {
				ptrY[i] = *(sin_func(a, b, val, size)); // Sets the value in the array to the sin function of the value
			} else if (func[0] == 'l') {
				ptrY[i] = *(linear_func(a, b, val, size)); // Sets the value in the array to the linear function of the value
			} else if (func[0] == 'e') {
				ptrY[i] = *(exp_func(a, b, val, size)); // Sets the value in the array to the exponential function of the value
			} else if (func[0] == 'q') {
				ptrY[i] = *(quadratic_func(a, b, val, size)); // Set the value in the array to the quadratic function of the value
			}
			break; // Ends the statement after the computation is made
		case 1:
			// If statements use first char of inputted string to determine what function to use
			if (func[0] == 's') {
				ptrY[i] = ((*(sin_func(a, b, val_plus, size)) - *(sin_func(a, b, val, size))) / h); // Sets the value in array to the 1st sin derivative of value
			} else if (func[0] == 'l') {
				ptrY[i] = ((*(linear_func(a, b, val_plus, size)) - *(linear_func(a, b, val, size))) / h); // Sets the value in array to the 1st linear function derivative of value
			} else if (func[0] == 'e') {
				ptrY[i] = ((*(exp_func(a, b, val_plus, size)) - *(exp_func(a, b, val, size))) / h); // Sets the value in array to the 1st exponential derivative of the value
			} else if (func[0] == 'q') {
				ptrY[i] = ((*(quadratic_func(a, b, val_plus, size)) - *(quadratic_func(a, b, val, size))) / h); // Sets the value in array to the 1st quadradic derivative of the value
			}
			break; // Ends the statement after the computation is made
		case 2:
			// If statements use first char of inputted string to determine what function to use
			if (func[0] == 's') {
				ptrY[i] = ((*(sin_func(a, b, val_plus, size)) - 2 * *(sin_func(a, b, val, size)) + *(sin_func(a, b, val_minus, size))) / (h*h)); // Sets the value in array to the 2nd sin derivative of value
			} else if (func[0] == 'l') {
				ptrY[i] = ((*(linear_func(a, b, val_plus, size)) - 2 * *(linear_func(a, b, val, size)) + *(linear_func(a, b, val_minus, size))) / (h*h)); // Sets the value in arrray to the 2nd linear derivative of value
			} else if (func[0] == 'e') {
				ptrY[i] = ((*(exp_func(a, b, val_plus, size)) - 2 * *(exp_func(a, b, val, size)) + *(exp_func(a,b,val_minus,size))) / (h*h)); // Sets value in array to the 2nd exponential derivative of value
			} else if (func[0] == 'q') {
				ptrY[i] = ((*(quadratic_func(a, b, val_plus, size)) - 2 * *(quadratic_func(a, b, val, size)) + *(quadratic_func(a, b, val, size))) / (h*h)); // Sets value in array to the 2nd quadratic derivative of value
			}
			break; // Ends the statement once the computation is made
		default:
			ptrY[i] = 3.14159; // The default case sets the value of the array to PI if the order is out of scope
		}
	}
	return ptrY; // Returns a pointer to the array of computed values
}


// Main method that takes the user input and number of arguments
int main(int argc, char* argv[]) {
	int size = argc - 2; // Computes the size of the array of values
	int h = atoi(argv[argc - 1]); // Sets h to be the last argument inputted
	double* valsArr = (double*) malloc(size*sizeof(double)); // Allocates memory for an array to store the values
	double* vals_plus = (double*) malloc(size*sizeof(double)); // Allocates memory for an array of the values +h;
	double* vals_minus = (double*) malloc(size*sizeof(double)); // Allocates memory for an array of the values -h;

	// For loop that assigns the values to valsArr, vals_plus, and vals_minus from inputted arguments
	for (int i = 0; i < size; i++) {
		valsArr[i] = atof(argv[i+1]);
		vals_plus[i] = valsArr[i] + h;
		vals_minus[i] = valsArr[i] - h;
	}

	//frees the memory allocated for all the arrays
	free(valsArr);
	free(vals_plus);
	free(vals_minus);

	return 0;
}
