#include <vector>;
#include <iostream>;
#include <tuple>;
using namespace std;

void printArr(std::vector<std::vector<std::vector<std::vector<float>>>> arr) {
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
	std::vector<std::vector<std::vector<std::vector<float>>>> pad = zero_pad(foo, 0);
	printArr(pad);


}