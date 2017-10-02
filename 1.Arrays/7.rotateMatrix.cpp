#include <iostream>
using namespace std;

void rotateMatrix (int ** matrix, int N) {
  int aux, max = N/2, end = N, ii, jj;
  for (int i=0; i<max; i++) {
    end--;
    for (int j=i; j<end; j++) {
      ii = N-i-1;
      jj = N-j-1;
      aux = matrix[i][j];
      matrix[i][j] = matrix[jj][i];
      matrix[jj][i] = matrix[ii][jj];
      matrix[ii][jj] = matrix[j][ii];
      matrix[j][ii] = aux;
    }
  }
}

int main() {
  int N=8;
  int ** matrix = new int * [N];
  for (int i=0; i<N; i++) {
    matrix[i] = new int [N];
    for (int j=0; j<N; j++) {
      matrix[i][j] = i+j;
    }
  }

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  rotateMatrix(matrix, N);
  cout << endl;

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  for (int i=0; i<N; i++) {
    delete [] matrix[i];
    }
  delete [] matrix;
}
