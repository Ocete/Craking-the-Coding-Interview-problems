#include <iostream>
using namespace std;

void zeroMatrix (int ** matrix, int M, int N) {
  bool firstRow = false, firstColumn = false;
  int i = 0;
  // Buscamos los 0s
  while (!firstRow && i<M) {
    if (matrix[i][0] == 0) firstRow = true;
    i++;
  }
  i=0;
  while (!firstColumn && i<N) {
    if (matrix[0][i] == 0) firstColumn = true;
    i++;
  }

  for (i=1; i<M; i++) {
    for (int j=1; j<N; j++) {
      if (matrix[i][j] == 0) {
        matrix[i][0] = matrix[0][j] = 0;
      }
    }
  }

  // Modificamos la matriz
  for (i=1; i<M; i++) {
    if (matrix[i][0] == 0) {
      for (int j=1; j<N; j++) {
        matrix[i][j] = 0;
      }
    }
  }
  for (int j=1; j<N; j++) {
    if (matrix[0][j] == 0) {
      for (i=1; i<M; i++) {
        matrix[i][j] = 0;
      }
    }
  }

  if (firstRow) {
    for (i=0; i<M; i++) {
      matrix[i][0] = 0;
    }
  }
  if (firstColumn) {
    for (i=0; i<N; i++) {
      matrix[0][i] = 0;
    }
  }
}

int main () {
  int M=5, N=8;
  int ** matrix = new int * [M];
  for (int i=0; i<M; i++) {
    matrix[i] = new int [N];
    for (int j=0; j<N; j++) {
      matrix[i][j] = i+j+1;
    }
  }

  matrix[1][0] = matrix[2][7] = 0;

  for (int i=0; i<M; i++) {
    for (int j=0; j<N; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  zeroMatrix(matrix, M, N);
  cout << endl;

  for (int i=0; i<M; i++) {
    for (int j=0; j<N; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  for (int i=0; i<M; i++) {
    delete [] matrix[i];
    }
  delete [] matrix;

}
