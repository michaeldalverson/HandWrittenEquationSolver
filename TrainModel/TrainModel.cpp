#include <vector>;
#include <iostream>;
#include <tuple>;
using namespace std;

void printArr2(vector<vector<float>> arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[0].size(); j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}
void printArr4(std::vector<std::vector<std::vector<std::vector<float>>>> arr) {
	int numCount = 0;
	std::vector<std::vector<std::vector<std::vector<float>>>> reX;
	for (int i = 0; i < arr.size(); i++) { //size of m
		std::vector<std::vector<std::vector<float>>> reX1;
		for (int j = 0; j < arr[0][0][0].size(); j++) { //size of c
			std::vector<std::vector<float>> reX2;
			for (int k = 0; k < arr[0].size(); k++) { //size of n_W
				std::vector<float> reX3;
				for (int l = 0; l < arr[0][0].size(); l++) { //size of n_H
					reX3.push_back(0); 
				}
				reX2.push_back(reX3);
			}
			reX1.push_back(reX2);
		}
		reX.push_back(reX1);
	}

	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[0].size(); j++) {
			for (int k = 0; k < arr[0][0].size(); k++) {
				for (int l = 0; l < arr[0][0][0].size(); l++) {
					reX[i][l][j][k] = arr[i][j][k][l];
				}
			}
		}
	}

	for (int i = 0; i < reX.size(); i++) {
		for (int j = 0; j < reX[0].size(); j++) {
			for (int k = 0; k < reX[0][0].size(); k++) {
				for (int l = 0; l < reX[0][0][0].size(); l++) {
					cout << reX[i][j][k][l] << " ";
					numCount = numCount + 1;
				}
				cout << "\n";
			}
			cout << "\n\n\n";
		}
		cout << "\n\n\n NEW SAMPLE \n\n\n";
	}
	cout << numCount;
}

std::vector<std::vector<std::vector<std::vector<float>>>> zero_pad(std::vector<std::vector<std::vector<std::vector<float>>>> X, float pad) {
	std::vector<std::vector<std::vector<std::vector<float>>>> reX;
	for (int i = 0; i < X.size(); i++) { //size of m
		std::vector<std::vector<std::vector<float>>> reX1;
		for (int j = 0; j < X[0][0][0].size(); j++) { //size of c
			std::vector<std::vector<float>> reX2;
			for (int k = 0; k < X[0].size(); k++) { //size of n_W
				std::vector<float> reX3;
				for (int l = 0; l< X[0][0].size(); l++) { //size of n_H
					reX3.push_back(0);
				}
				reX2.push_back(reX3);
			}
			reX1.push_back(reX2);
		}
		reX.push_back(reX1);
	}

	for (int i = 0; i < X.size(); i++) {
		for (int j = 0; j < X[0].size(); j++) {
			for (int k = 0; k < X[0][0].size(); k++) {
				for (int l = 0; l < X[0][0][0].size(); l++) {
					reX[i][l][j][k] = X[i][j][k][l];
				}
			}
		}
	}

	std::vector<std::vector<std::vector<std::vector<float>>>> padded;
	for (int i = 0; i < reX.size(); i++) {
		std::vector<std::vector<std::vector<float>>> padded1;
		for (int j = 0; j < reX[0].size(); j++) {
			std::vector<std::vector<float>> padded2;
			for (int k = 0; k < reX[0][0].size() + (2 * pad); k++) {
				std::vector<float> paddedRow;
				for (int l = 0; l < reX[0][0][0].size() + (2 * pad); l++) {
					paddedRow.push_back(0);
				}
				padded2.push_back(paddedRow);
			}
			for (int k = pad; k < reX[0][0][0].size() + pad; k++) {
				for (int l = pad; l < reX[0][0].size() + pad; l++) {
					padded2[k][l] = reX[i][j][k - pad][l - pad];
				}
			}
			padded1.push_back(padded2);
		}
		padded.push_back(padded1);
	}

	std::vector<std::vector<std::vector<std::vector<float>>>> reP;
	for (int i = 0; i < padded.size(); i++) { //size of m
		std::vector<std::vector<std::vector<float>>> reP1;
		for (int j = 0; j < padded[0][0].size(); j++) { //size of n_W
			std::vector<std::vector<float>> reP2;
			for (int k = 0; k < padded[0][0][0].size(); k++) { //size of n_H
				std::vector<float> reP3;
				for (int l = 0; l < X[0].size(); l++) { //size of n_C
					reP3.push_back(0);
				}
				reP2.push_back(reP3);
			}
			reP1.push_back(reP2);
		}
		reP.push_back(reP1);
	}

	for (int i = 0; i < padded.size(); i++) {
		for (int j = 0; j < padded[0].size(); j++) {
			for (int k = 0; k < padded[0][0].size(); k++) {
				for (int l = 0; l < padded[0][0][0].size(); l++) {
					reP[i][k][l][j] = padded[i][j][k][l];
				}
			}
		}
	}

			return reP;
}

float conv_single_step(std::vector<std::vector<std::vector<float>>> a_slice_prev, std::vector<std::vector<std::vector<float>>> W, std::vector<std::vector<std::vector<float>>> b) {
	float Z = 0;
	for (int f1 = 0; f1 < a_slice_prev.size(); f1++) {
		for (int f2 = 0; f2 < a_slice_prev[f1].size(); f2++) {
			for (int c = 0; c < a_slice_prev[f1][f2].size(); c++) {
				Z = Z + (a_slice_prev[f1][f2][c] * W[f1][f2][c]);
			}
		}
	}
	Z = Z + b[0][0][0];
	return Z;
}


std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>, 
	std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
	std::vector<std::vector<std::vector<std::vector<float>>>>, 
	std::vector<std::vector<std::vector<std::vector<float>>>>, 
	tuple<int, int>>>  
	conv_forward(std::vector<std::vector<std::vector<std::vector<float>>>> A_prev, 
		std::vector<std::vector<std::vector<std::vector<float>>>> W, 
		std::vector<std::vector<std::vector<std::vector<float>>>> b, 
		std::tuple<int, int> hparameters) {

	// Retreive dimensions from A_prev's shape
	int m = A_prev.size();
	int n_H_prev = A_prev[0].size();
	int n_W_prev = A_prev[0][0].size();
	int n_C_prev = A_prev[0][0][0].size();

	//Retrieve dimensions from W's shape
	int f = W.size();
	int n_C = W[0][0][0].size();

	//Retrieve infromation from "hparameters"
	int stride = std::get<0>(hparameters);
	int pad = std::get<1>(hparameters);

	//Compute the dimensions of the CONV output volume using the formula given above.
	int n_H = int((n_H_prev + (2 * pad) - f) / stride) + 1;
	int n_W = int((n_W_prev + (2 * pad) - f) / stride) + 1;

	//Initialize the output volume Z with zeros
	std::vector<std::vector<std::vector<std::vector<float>>>> Z;
	for (int i = 0; i < m; i++) {
		std::vector<std::vector<std::vector<float>>> Z1;
		for (int j = 0; j < n_H; j++) {
			std::vector<std::vector<float>> Z2;
			for (int k = 0; k < n_W; k++) {
				std::vector<float> Z3;
				for (int l = 0; l < n_C; l++) {
					Z3.push_back(0);
				}
				Z2.push_back(Z3);
			}
			Z1.push_back(Z2);
		}
		Z.push_back(Z1);
	}

	//Create A_prev_pad by padding A_prev
	std::vector<std::vector<std::vector<std::vector<float>>>> A_prev_pad = zero_pad(A_prev, pad);

	for (int i = 0; i < m; i++) {
		std::vector<std::vector<std::vector<float>>> a_prev_pad;
		for (int j = 0; j < n_H; j++) {
			std::vector<std::vector<float>> a_prev_pad1;
			for (int k = 0; k < n_W; k++) {
				std::vector<float> a_prev_pad2;
				for (int l = 0; l < n_C; l++) {
					a_prev_pad2.push_back(A_prev_pad[i][j][k][l]);
				}
				a_prev_pad1.push_back(a_prev_pad2);
			}
			a_prev_pad.push_back(a_prev_pad1);
		}
		for (int h = 0; h < n_H; h++) {
			for (int w = 0; w < n_W; w++) {
				for (int c = 0; c < n_C; c++) {
					int vert_start = h * stride;
					int vert_end = h * stride + f;
					int horiz_start = w * stride;
					int horiz_end = w * stride + f;

					std::vector<std::vector<std::vector<float>>> a_slice_prev;
					for (int x = vert_start; x < vert_end; x++) {
						std::vector<std::vector<float>> a_slice_prev1;
						for (int y = horiz_start; y < horiz_end; y++) {
							std::vector<float> a_slice_prev2;
							for (int z = 0; z < n_C; z++) {
								a_slice_prev2.push_back(a_prev_pad[x][y][z]);
							}
							a_slice_prev1.push_back(a_slice_prev2);
						}
						a_slice_prev.push_back(a_slice_prev1);
					}

					std::vector<std::vector<std::vector<float>>> WSlice;
					for (int x = 0; x < n_H; x++) {
						std::vector<std::vector<float>> WSlice1;
						for (int y = 0; y < n_W; y++) {
							std::vector<float> WSlice2;
							for (int z = 0; z < n_C; z++) {
								WSlice2.push_back(W[x][y][z][c]);
							}
							WSlice1.push_back(WSlice2);
						}
						WSlice.push_back(WSlice1);
					}

					std::vector<std::vector<std::vector<float>>> bSlice;
					for (int x = 0; x < n_H; x++) {
						std::vector<std::vector<float>> bSlice1;
						for (int y = 0; y < n_W; y++) {
							std::vector<float> bSlice2;
							for (int z = 0; z < n_C; z++) {
								bSlice2.push_back(b[x][y][z][c]);
							}
							bSlice1.push_back(bSlice2);
						}
						bSlice.push_back(bSlice1);
					}
					
					Z[i][h][w][c] = conv_single_step(a_slice_prev, WSlice, bSlice);

				
					
				}
			}
		}
	}

	std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
		std::vector<std::vector<std::vector<std::vector<float>>>>,
		std::vector<std::vector<std::vector<std::vector<float>>>>,
		tuple<int, int>> cache{ A_prev, W, b, hparameters };

	std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>, 
		std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
		std::vector<std::vector<std::vector<std::vector<float>>>>,
		std::vector<std::vector<std::vector<std::vector<float>>>>,
		tuple<int, int>>> output{ Z, cache };

	return output;
	

 
}

std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
	std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
	tuple<int, int>>>
	pool_forward(std::vector<std::vector<std::vector<std::vector<float>>>> A_prev,
		std::tuple<int, int> hparameters, std::string mode) {

	// Retreive dimensions from A_prev's shape
	int m = A_prev.size();
	int n_H_prev = A_prev[0].size();
	int n_W_prev = A_prev[0][0].size();
	int n_C_prev = A_prev[0][0][0].size();

	//Retrieve infromation from "hparameters"
	int stride = std::get<0>(hparameters);
	int f = std::get<1>(hparameters);

	//Define the dimensions of the output
	int n_H = int(1 + (n_H_prev - f) / stride);
	int n_W = int(1 + (n_W_prev - f) / stride);
	int n_C = n_C_prev;

	//Initialize the output volume A with zeros
	std::vector<std::vector<std::vector<std::vector<float>>>> A;
	for (int i = 0; i < m; i++) {
		std::vector<std::vector<std::vector<float>>> A1;
		for (int j = 0; j < n_H; j++) {
			std::vector<std::vector<float>> A2;
			for (int k = 0; k < n_W; k++) {
				std::vector<float> A3;
				for (int l = 0; l < n_C; l++) {
					A3.push_back(0);
				}
				A2.push_back(A3);
			}
			A1.push_back(A2);
		}
		A.push_back(A1);
	}

	for (int i = 0; i < m; i++) {
		for (int h = 0; h < n_H; h++) {
			for (int w = 0; w < n_W; w++) {
				for (int c = 0; c < n_C; c++) {

					int vert_start = h* stride;
					int vert_end = h * stride + f;
					int horiz_start = w * stride;
					int horiz_end = w * stride + f;

					std::vector<std::vector<float>> a_prev_slice;
					for (int x = vert_start; x < vert_end; x++) {
						std::vector<float> a_prev_slice1;
						for (int y = horiz_start; y < horiz_end; y++) {
							a_prev_slice1.push_back(A_prev[i][x][y][c]);
						}
						a_prev_slice.push_back(a_prev_slice1);
					}

					if (mode == "max"){
						float max = 0;
						for (int x = 0; x < a_prev_slice.size(); x++) {
							for (int y = 0; y < a_prev_slice[0].size(); y++) {
								if (a_prev_slice[x][y] > max) {
									max = a_prev_slice[x][y];
								}
							}
						}
						A[i][h][w][c] = max;
					}
					else if (mode == "average") {
						float sum = 0;
						float count = 0;
						for (int x = 0; x < a_prev_slice.size(); x++) {
							for (int y = 0; y < a_prev_slice[0].size(); y++) {
								sum = sum + a_prev_slice[x][y];
								count = count + 1;
							}
						}
						A[i][h][w][c] = sum / count;
					}
				}
			}
		}
	}

	std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
		tuple<int, int>> cache{ A_prev, hparameters };

	std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
		std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
		tuple<int, int>>> output{ A, cache };

	return output;
}

std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>, 
	std::vector<std::vector<std::vector<std::vector<float>>>>,
	std::vector<std::vector<std::vector<std::vector<float>>>>>
	conv_backward(std::vector<std::vector<std::vector<std::vector<float>>>> dZ,
		std::tuple<std::vector<std::vector<std::vector<std::vector<float>>>>,
		std::vector<std::vector<std::vector<std::vector<float>>>>,
		vector<std::vector<std::vector<std::vector<float>>>>,
		tuple<int, int>> cache) {

	//Retrieve information from "cache"
	vector<vector<vector<vector<float>>>> A_prev = get<0>(cache);
	vector<vector<vector<vector<float>>>> W = get<1>(cache);
	vector<vector<vector<vector<float>>>> b = get<2>(cache);
	tuple<int, int> hparameters = get<3>(cache);

	//Retrieve dimensions from A_prev's shape
	int m = A_prev.size();
	int n_H_prev = A_prev[0].size();
	int n_W_prev = A_prev[0][0].size();
	int n_C_prev = A_prev[0][0][0].size();

	//Retrieve infromation from W's shape
	int f = W.size();
	int n_C = W[0][0][0].size();

	//Retrieve information from "hparameters"
	int stride = get<0>(hparameters);
	int pad = get<1>(hparameters);

	//Retrieve dimensions from dZ's shape
	int n_H = dZ[0].size();
	int n_W = dZ[0][0].size();

	//Initialize dA_prev with all zeros
	std::vector<std::vector<std::vector<std::vector<float>>>> dA_prev;
	for (int i = 0; i < m; i++) {
		std::vector<std::vector<std::vector<float>>> dA_prev1;
		for (int j = 0; j < n_H_prev; j++) {
			std::vector<std::vector<float>> dA_prev2;
			for (int k = 0; k < n_W_prev; k++) {
				std::vector<float> dA_prev3;
				for (int l = 0; l < n_C_prev; l++) {
					dA_prev3.push_back(0);
				}
				dA_prev2.push_back(dA_prev3);
			}
			dA_prev1.push_back(dA_prev2);
		}
		dA_prev.push_back(dA_prev1);
	}

	//Initialize dW with all zeros
	std::vector<std::vector<std::vector<std::vector<float>>>> dW;
	for (int i = 0; i < f; i++) {
		std::vector<std::vector<std::vector<float>>> dW1;
		for (int j = 0; j < f; j++) {
			std::vector<std::vector<float>> dW2;
			for (int k = 0; k < n_C_prev; k++) {
				std::vector<float> dW3;
				for (int l = 0; l < n_C; l++) {
					dW3.push_back(0);
				}
				dW2.push_back(dW3);
			}
			dW1.push_back(dW2);
		}
		dW.push_back(dW1);
	}

	//Initialize db with all zeros
	std::vector<std::vector<std::vector<std::vector<float>>>> db;
	for (int i = 0; i < 1; i++) {
		std::vector<std::vector<std::vector<float>>> db1;
		for (int j = 0; j < 1; j++) {
			std::vector<std::vector<float>> db2;
			for (int k = 0; k < 1; k++) {
				std::vector<float> db3;
				for (int l = 0; l < n_C; l++) {
					db3.push_back(0);
				}
				db2.push_back(db3);
			}
			db1.push_back(db2);
		}
		db.push_back(db1);
	}

	//Pad A_prev and dA_prev
	vector<vector<vector<vector<float>>>> A_prev_pad = zero_pad(A_prev, pad);
	vector<vector<vector<vector<float>>>> dA_prev_pad = zero_pad(dA_prev, pad);

	for (int i = 0; i < m; i++) {

		//Select ith training example from A_prev and dA_prev_pad
		vector<vector<vector<float>>> a_prev_pad = A_prev_pad[i];
		vector<vector<vector<float>>> da_prev_pad = dA_prev_pad[i];

		for (int h = 0; h < n_H; h++) {
			for (int w = 0; w < n_W; w++) {
				for (int c = 0; c < n_C; c++) {

					//Find the corners of the current "slice"
					int vert_start = h;
					int vert_end = vert_start + f;
					int horiz_start = w;
					int horiz_end = horiz_start + f;

					//Use the corners to define the slice from a_prev_pad
					vector<vector<vector<float>>> a_slice;
					for (int x = vert_start; x < vert_end; x++) {
						vector<vector<float>> a_slice1;
						for (int y = horiz_start; y < horiz_end; y++) {
							vector<float> a_slice2;
							for (int z = 0; z < a_prev_pad[0][0].size(); z++) {
								a_slice2.push_back(a_prev_pad[x][y][z]);
							}
							a_slice1.push_back(a_slice2);
						}
						a_slice.push_back(a_slice1);
					}

					//Update gradients for the window and the filter's parameters
					std::vector<std::vector<std::vector<float>>> WZSlice;
					for (int x = 0; x < n_H; x++) {
						std::vector<std::vector<float>> WZSlice1;
						for (int y = 0; y < n_W; y++) {
							std::vector<float> WZSlice2;
							for (int z = 0; z < n_C; z++) {
								WZSlice2.push_back(W[x][y][z][c] * dZ[i][h][w][c]);
							}
							WZSlice1.push_back(WZSlice2);
						}
						WZSlice.push_back(WZSlice1);
					}

					for (int x = vert_start; x < vert_end; x++) {
						for (int y = horiz_start; y < horiz_end; y++) {
							for (int z = 0; z < da_prev_pad[0][0].size(); z++) {
								da_prev_pad[x][y][z] = da_prev_pad[x][y][z] + WZSlice[x][y][z];
							}
						}
					}

					std::vector<std::vector<std::vector<float>>> aZSlice;
					for (int x = 0; x < a_slice.size(); x++) {
						std::vector<std::vector<float>> aZSlice1;
						for (int y = 0; y < a_slice[0].size(); y++) {
							std::vector<float> aZSlice2;
							for (int z = 0; z < a_slice[0][0].size(); z++) {
								aZSlice2.push_back(a_slice[x][y][z] * dZ[i][h][w][c]);
							}
							aZSlice1.push_back(aZSlice2);
						}
						aZSlice.push_back(aZSlice1);
					}

					for (int x = 0; x < dW.size(); x++) {
						for (int y = 0; y < dW[0].size(); y++) {
							for (int z = 0; z < dW[0][0].size(); z++) {
								dW[x][y][z][c] = dW[x][y][z][c] + aZSlice[x][y][z];
							}
						}
					}

					for (int x = 0; x < db.size(); x++) {
						for (int y = 0; y < db[0].size(); y++) {
							for (int z = 0; z < db[0][0].size(); z++) {
								db[x][y][z][c] = db[x][y][z][c] + dZ[i][h][w][c];
							}
						}
					}
				}
			}
		}
		//Set the ith training example's dA_prev to the unpadded da_prev_pad
		vector<vector<vector<float>>> da_prev_UNpad;
		for (int x = pad; x < da_prev_pad.size() - pad; x++) {
			vector<vector<float>> da_prev_UNpad1;
			for (int y = pad; y < da_prev_pad[0].size() - pad; y++) {
				vector<float> da_prev_UNpad2;
				for (int z = 0; z < da_prev_pad[0][0].size(); z++) {
					da_prev_UNpad2.push_back(da_prev_pad[x][y][z]);
				}
				da_prev_UNpad1.push_back(da_prev_UNpad2);
			}
			da_prev_UNpad.push_back(da_prev_UNpad1);
		}

		for (int x = 0; x < dA_prev[0].size(); x++) {
			for (int y = 0; y < dA_prev[0][0].size(); y++) {
				for (int z = 0; z < dA_prev[0][0][0].size(); z++) {
					dA_prev[i][x][y][z] = da_prev_pad[x][y][z];
				}
			}
		}
	}

	tuple<vector<vector<vector<vector<float>>>>,
		vector<vector<vector<vector<float>>>>,
		vector<vector<vector<vector<float>>>>> output{ dA_prev, dW, db };

	return output;
}

vector<vector<float>> create_mask_from_window(vector<vector<float>> x) {
	vector<vector<float>> mask;
	float max = x[0][0];
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x[0].size(); j++) {
			if (x[i][j] > max) {
				max = x[i][j];
			}
		}
	}
	for (int i = 0; i < x.size(); i++) {
		vector<float> mask1;
		for (int j = 0; j < x[0].size(); j++) {
			if (x[i][j] == max) {
				mask1.push_back(1);
			}
			else {
				mask1.push_back(0);
			}
		}
		mask.push_back(mask1);
	}
	return mask;

}

vector<vector<float>> distribute_value(float dz, tuple<int,int> shape) {
	
	//Retrieve dimensions from shape
	int n_H = get<0>(shape);
	int n_W = get<1>(shape);

	//Compute the value to distribute on the matrix
	float average = dz / (n_H * n_W);

	//Create a matrix where every entry is the "average" value
	vector<vector<float>> a;
	for (int i = 0; i < n_H; i++) {
		vector<float> a1;
		for (int j = 0; j < n_W; j++) {
			a1.push_back(average);
		}
		a.push_back(a1);
	}

	return a;
}

vector<vector<vector<vector<float>>>> pool_backward(vector<vector<vector<vector<float>>>> dA,
	tuple<vector<vector<vector<vector<float>>>>,
	tuple<int, int>> cache, string mode) {

	//Retrieve information from cache
	vector<vector<vector<vector<float>>>> A_prev = get<0>(cache);
	tuple<int, int> hparameters = get<1>(cache);

	//Retrieve hyperparameters from "hparameters"
	int stride = get<0>(hparameters);
	int f = get<1>(hparameters);

	//Retrieve dimensions from A_prev's shape and dA's shape
	int m = A_prev.size();
	int n_H_prev = A_prev[0].size();
	int n_W_prev = A_prev[0][0].size();
	int n_C_prev = A_prev[0][0][0].size();

	int n_H = dA[0].size();
	int n_W = dA[0][0].size();
	int n_C = dA[0][0][0].size();

	//Initialize the output volume dA_prev with zeros
	std::vector<std::vector<std::vector<std::vector<float>>>> dA_prev;
	for (int i = 0; i < m; i++) {
		std::vector<std::vector<std::vector<float>>> dA_prev1;
		for (int j = 0; j < n_H_prev; j++) {
			std::vector<std::vector<float>> dA_prev2;
			for (int k = 0; k < n_W_prev; k++) {
				std::vector<float> dA_prev3;
				for (int l = 0; l < n_C_prev; l++) {
					dA_prev3.push_back(0);
				}
				dA_prev2.push_back(dA_prev3);
			}
			dA_prev1.push_back(dA_prev2);
		}
		dA_prev.push_back(dA_prev1);
	}

	for (int i = 0; i < m; i++) {
		//select training example from A_prev
		vector<vector<vector<float>>> a_prev = A_prev[i];
		for (int h = 0; h < n_H; h++) {
			for (int w = 0; w < n_W; w++) {
				for (int c = 0; c < n_C; c++) {

					//Find the corners of the current "slice"
					int vert_start = h;
					int vert_end = vert_start + f;
					int horiz_start = w;
					int horiz_end = horiz_start + f;

					//Compute the backward propagation in both modes
					if (mode == "max") {
						//Use the corners and "c" to define the current slice from a_prev
						vector<vector<float>> a_prev_slice;
						for (int x = vert_start; x < vert_end; x++) {
							vector<float> a_prev_slice1;
							for (int y = horiz_start; y < horiz_end; y++) {
								a_prev_slice1.push_back(a_prev[x][y][c]);
							}
							a_prev_slice.push_back(a_prev_slice1);
						}

						//Create the mask from a_prev_slice
						vector<vector<float>> mask = create_mask_from_window(a_prev_slice);

						vector<vector<float>> maskdA;
						for (int x = 0; x < mask.size(); x++) {
							vector<float> maskdA1;
							for (int y = 0; y < mask[0].size(); y++) {
								maskdA1.push_back(mask[x][y] * dA[i][h][w][c]);
							}
							maskdA.push_back(maskdA1);
						}

						//Set dA_prev to be dA_prev + (the mask multiplied by the correct entry of dA)
						for (int x = vert_start; x < vert_end; x++) {
							for (int y = horiz_start; y < horiz_end; y++) {
								dA_prev[i][x][y][c] = dA_prev[i][x][y][c] + maskdA[x][y];
							}
						}
					}
					else if (mode == "average") {
						//Get the value a from dA
						float da = dA[i][h][w][c];

						//Define the shape of the filter as fxf
						tuple<int, int> shape{ f, f };

						vector<vector<float>> distributed = distribute_value(da, shape);

						for (int x = vert_start; x < vert_end; x++) {
							for (int y = horiz_start; y < horiz_end; y++) {
								dA_prev[i][x][y][c] = dA_prev[i][x][y][c] + distributed[x][y];
							}
						}
					}
				}
			}
		}
	}
	return dA_prev;
}

int main() {
	std::vector<std::vector<std::vector<std::vector<float>>>> foo;
	for (int i = 0; i < 10; i++) {
		std::vector<std::vector<std::vector<float>>> foo1;
		for (int j = 0; j < 10; j++) {
			std::vector<std::vector<float>> foo2;
			for (int k = 0; k < 10; k++) {
				std::vector<float> foo3;
				for (int l = 0; l < 10; l++) {
					foo3.push_back(1);
				}
				foo2.push_back(foo3);
			}
			foo1.push_back(foo2);
		}
		foo.push_back(foo1);
	}
	vector<vector<vector<vector<float>>>> pad = zero_pad(foo, 0);
	printArr4(pad);

	tuple<int, int> tup {2, 2};
	vector<vector<float>> val = distribute_value(2, tup);
	printArr2(val);


}