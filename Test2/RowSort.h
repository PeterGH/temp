#pragma once
namespace My {

	// ColumnSort is described in MIT Introduction to Algorithms 3rd edition Chapter 8 problem 8-7.
	// Sort an array of r rows and s columns such that
	// 1. r must be even
	// 2. s must be a divisor of r
	// 3. r >= 2s^2
	// The steps are
	// 0. Given an array
	//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
	//                             ......
	//                             ......
	//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
	//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
	// 1. Sort each column
	// 2. Transpose the array. Turn the leftmost column into top r/s rows in order, and then do the same thing for the rest of columns in order
	//     (0,0)     (1,0)       (2,0)       ...... (s-2,0)    (s-1,0)
	//     (s,0)     (s+1,0)     (s+2,0)     ...... (2s-2,0)   (2s-1,0)
	//                                       ......
	//     (r-s,0)   (r-s+1,0)   (r-s+2,0)   ...... (r-2,0)    (r-1,0)
	//     (0,1)     (1,1)       (2,1)       ...... (s-2,1)    (s-1,1)
	//     (s,1)     (s+1,1)     (s+2,1)     ...... (2s-2,1)   (2s-1,1)
	//                                       ......
	//     (r-s,1)   (r-s+1,1)   (r-s+2,1)   ...... (r-2,1)    (r-1,1)
	//                                       ......
	//                                       ......
	//     (0,s-1)   (1,s-1)     (2,s-1)     ...... (s-2,s-1)  (s-1,s-1)
	//     (s,s-1)   (s+1,s-1)   (s+2,s-1)   ...... (2s-2,s-1) (2s-1,s-1)
	//                                       ......
	//     (r-s,s-1) (r-s+1,s-1) (r-s+2,s-1) ...... (r-2,s-1)  (r-1,s-1)
	// 3. Sort each column
	// 4. Revert step 2
	//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
	//                             ......
	//                             ......
	//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
	//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
	// 5. Sort each column
	// 6. Shift leftmost column down by r/2 and into the top of its right next column. Do the same for the rest of columns in order
	//               (r/2,0)   (r/2,1)   (r/2,2)   ...... (r/2,s-3)   (r/2,s-2)   (r/2,s-1)
	//               (r/2+1,0) (r/2+1,1) (r/2+1,2) ...... (r/2+1,s-3) (r/2+1,s-2) (r/2+1,s-1)
	//               (r/2+2,0) (r/2+2,1) (r/2+2,2) ...... (r/2+2,s-3) (r/2+2,s-2) (r/2+2,s-1)
	//                                             ......
	//                                             ......
	//               (r-1,0)   (r-1,1)   (r-1,2)   ...... (r-1,s-3)   (r-1,s-2)   (r-1,s-1)
	//     (0,0)     (0,1)     (0,2)     ......           (0,s-2)     (0,s-1)
	//     (1,0)     (1,1)     (1,2)     ......           (1,s-2)     (1,s-1)
	//     (2,0)     (2,1)     (2,2)     ......           (2,s-2)     (2,s-1)
	//                                   ......
	//                                   ......
	//     (r/2-2,0) (r/2-2,1) (r/2-2,2) ......           (r/2-2,s-2) (r/2-2,s-1)
	//     (r/2-1,0) (r/2-1,1) (r/2-1,2) ......           (r/2-1,s-2) (r/2-1,s-1)
	// 7. Sort each column
	// 8. Revert step 6
	//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
	//                             ......
	//                             ......
	//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
	//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)

	class ColumnSort {

	};

	// RowSort is a transpose of ColumnSort described in MIT Introduction to Algorithms 3rd edition Chapter 8 problem 8-7.
	// Sort an array of s rows and r columns such that
	// 1. r must be even
	// 2. s must be a divisor of r
	// 3. r >= 2s^2
	// The steps are
	// 0. Given an array
	//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
	//                             ......
	//                             ......
	//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
	//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
	// 1. Sort each row
	// 2. Transpose the array. Turn the topmost row into left r/s columns in order, and then do the same thing for the rest of rows in order
	//     (0,0)   (s,0)    ...... (r-s,0)   (0,1)   (s,1)    ...... (r-s,1)   ...... (0,s-1)   (s,s-1)    ...... (r-s,s-1)
	//     (1,0)   (s+1,0)  ...... (r-s+1,0) (1,1)   (s+1,1)  ...... (r-s+1,1) ...... (1,s-1)   (s+1,s-1)  ...... (r-s+1,s-1)
	//     (2,0)   (s+2,0)  ...... (r-s+2,0) (2,1)   (s+2,1)  ...... (r-s+2,1) ...... (2,s-1)   (s+2,s-1)  ...... (r-s+2,s-1)
	//                                                                         ......
	//                                                                         ......
	//     (s-2,0) (2s-2,0) ...... (r-2,0)   (s-2,1) (2s-2,1) ...... (r-2,1)   ...... (s-2,s-1) (2s-2,s-1) ...... (r-2,s-1)
	//     (s-1,0) (2s-1,0) ...... (r-1,0)   (s-1,1) (2s-1,1) ...... (r-1,1)   ...... (s-1,s-1) (2s-1,s-1) ...... (r-1,s-1)
	// 3. Sort each row
	// 4. Revert step 2
	//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
	//                             ......
	//                             ......
	//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
	//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
	// 5. Sort each row
	// 6. Shift topmost row right by r/2 and into the left of its down next row. Do the same for the rest of rows in order
	//                                                                  (0,0)   (0,1)   (0,2)   ...... (0,r/2-2)   (0,r/2-1)
	//     (0,r/2)   (0,r/2+1)   (0,r/2+2)   ...... (0,r-2)   (0,r-1)   (1,0)   (1,1)   (1,2)   ...... (1,r/2-2)   (1,r/2-1)
	//     (1,r/2)   (1,r/2+1)   (1,r/2+2)   ...... (1,r-2)   (1,r-1)   (2,0)   (2,1)   (2,2)   ...... (2,r/2-2)   (2,r/2-1)
	//                                       ......                                             ......
	//                                       ......                                             ......
	//     (s-3,r/2) (s-3,r/2+1) (s-3,r/2+2) ...... (s-3,r-2) (s-3,r-1) (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r/2-2) (s-2,r/2-1)
	//     (s-2,r/2) (s-2,r/2+1) (s-2,r/2+2) ...... (s-2,r-2) (s-2,r-1) (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r/2-2) (s-1,r/2-1)
	//     (s-1,r/2) (s-1,r/2+1) (s-1,r/2+2) ...... (s-1,r-2) (s-1,r-1)
	// 7. Sort each row
	// 8. Revert step 6
	//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
	//                             ......
	//                             ......
	//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
	//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)

	class RowSort {
	};
}