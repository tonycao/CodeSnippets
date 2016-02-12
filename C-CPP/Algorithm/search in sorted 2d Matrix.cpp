bool stepWise(int mat[][N_MAX], int N, int target,
              int &row, int &col) {
  if (target < mat[0][0] || target > mat[N-1][N-1]) return false;
  row = 0;
  col = N-1;
  while (row <= N-1 && col >= 0) {
    if (mat[row][col] < target)
      row++;
    else if (mat[row][col] > target)
      col--;
    else
      return true;
  }
  return false;
}

//binary partition
bool binPart(int mat[][N_MAX], int M, int N, int target, int l, int u, int r, int d, int &targetRow, int &targetCol) {
  if (l > r || u > d) return false;
  if (target < mat[u][l] || target > mat[d][r]) return false;
  int mid = l + (r-l)/2;
  int row = u;
  while (row <= d && mat[row][mid] <= target) {
    if (mat[row][mid] == target) {
      targetRow = row;
      targetCol = mid;
      return true;
    }
    row++;
  }
  return binPart(mat, M, N, target, mid+1, u, r, row-1, targetRow, targetCol) ||
         binPart(mat, M, N, target, l, row, mid-1, d, targetRow, targetCol);
}

bool binPart(int mat[][N_MAX], int N, int target, int &row, int &col) {
  return binPart(mat, N, N, target, 0, 0, N-1, N-1, row, col);
}
