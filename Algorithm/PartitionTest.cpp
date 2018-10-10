#include "Header.h"

void PartitionTest::Init(void)
{
	Add("ByOrders", [&]() {
		{
			int A[] = { 1 };
			int I[] = { 0 };
			Partition::PartitionArrayByOrders(A, 0, 0, I, 0, 0);
			ASSERT1(A[0] == 1);
		}
		{
			int A[] = { 1, 2 };
			int I1[] = { 0 };
			Partition::PartitionArrayByOrders(A, 0, 1, I1, 0, 0);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);

			int I2[] = { 1 };
			Partition::PartitionArrayByOrders(A, 0, 1, I2, 0, 0);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);

			int I3[] = { 0, 1 };
			Partition::PartitionArrayByOrders(A, 0, 1, I3, 0, 1);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);

			int B1[] = { 2, 1 };
			Partition::PartitionArrayByOrders(B1, 0, 1, I1, 0, 0);
			ASSERT1(B1[0] == 1);
			ASSERT1(B1[1] == 2);

			int B2[] = { 2, 1 };
			Partition::PartitionArrayByOrders(B2, 0, 1, I2, 0, 0);
			ASSERT1(B2[0] == 1);
			ASSERT1(B2[1] == 2);

			int B3[] = { 2, 1 };
			Partition::PartitionArrayByOrders(B3, 0, 1, I3, 0, 1);
			ASSERT1(B3[0] == 1);
			ASSERT1(B3[1] == 2);
		}
		{
			int A[] = { 1, 2, 3 };
			int I1[] = { 0 };
			Partition::PartitionArrayByOrders(A, 0, 2, I1, 0, 0);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int I2[] = { 1 };
			Partition::PartitionArrayByOrders(A, 0, 2, I2, 0, 0);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int I3[] = { 2 };
			Partition::PartitionArrayByOrders(A, 0, 2, I3, 0, 0);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int I4[] = { 0, 1 };
			Partition::PartitionArrayByOrders(A, 0, 2, I4, 0, 1);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int I5[] = { 0, 2 };
			Partition::PartitionArrayByOrders(A, 0, 2, I5, 0, 1);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int I6[] = { 1, 2 };
			Partition::PartitionArrayByOrders(A, 0, 2, I6, 0, 1);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int I7[] = { 0, 1, 2 };
			Partition::PartitionArrayByOrders(A, 0, 2, I7, 0, 2);
			ASSERT1(A[0] == 1);
			ASSERT1(A[1] == 2);
			ASSERT1(A[2] == 3);

			int B1[] = { 2, 1, 3 };
			Partition::PartitionArrayByOrders(B1, 0, 2, I1, 0, 0);
			ASSERT1(B1[0] == 1);
			ASSERT1(B1[1] > B1[0]);
			ASSERT1(B1[2] > B1[0]);

			int B2[] = { 2, 3, 1 };
			Partition::PartitionArrayByOrders(B2, 0, 2, I1, 0, 0);
			ASSERT1(B2[0] == 1);
			ASSERT1(B2[1] > B2[0]);
			ASSERT1(B2[2] > B2[0]);

			int B3[] = { 3, 1, 2 };
			Partition::PartitionArrayByOrders(B3, 0, 2, I1, 0, 0);
			ASSERT1(B3[0] == 1);
			ASSERT1(B3[1] > B3[0]);
			ASSERT1(B3[2] > B3[0]);

			int B4[] = { 3, 2, 1 };
			Partition::PartitionArrayByOrders(B4, 0, 2, I1, 0, 0);
			ASSERT1(B4[0] == 1);
			ASSERT1(B4[1] > B4[0]);
			ASSERT1(B4[2] > B4[0]);

			int B5[] = { 2, 1, 3 };
			Partition::PartitionArrayByOrders(B5, 0, 2, I2, 0, 0);
			ASSERT1(B5[0] == 1);
			ASSERT1(B5[1] == 2);
			ASSERT1(B5[2] == 3);

			int B6[] = { 2, 3, 1 };
			Partition::PartitionArrayByOrders(B6, 0, 2, I2, 0, 0);
			ASSERT1(B6[0] == 1);
			ASSERT1(B6[1] == 2);
			ASSERT1(B6[2] == 3);

			int B7[] = { 3, 1, 2 };
			Partition::PartitionArrayByOrders(B7, 0, 2, I2, 0, 0);
			ASSERT1(B7[0] == 1);
			ASSERT1(B7[1] == 2);
			ASSERT1(B7[2] == 3);

			int B8[] = { 3, 2, 1 };
			Partition::PartitionArrayByOrders(B8, 0, 2, I2, 0, 0);
			ASSERT1(B8[0] == 1);
			ASSERT1(B8[1] == 2);
			ASSERT1(B8[2] == 3);

			int B9[] = { 2, 1, 3 };
			Partition::PartitionArrayByOrders(B9, 0, 2, I3, 0, 0);
			ASSERT1(B9[0] < B9[2]);
			ASSERT1(B9[1] < B9[2]);
			ASSERT1(B9[2] == 3);

			int B10[] = { 2, 3, 1 };
			Partition::PartitionArrayByOrders(B10, 0, 2, I3, 0, 0);
			ASSERT1(B10[0] < B10[2]);
			ASSERT1(B10[1] < B10[2]);
			ASSERT1(B10[2] == 3);

			int B11[] = { 3, 1, 2 };
			Partition::PartitionArrayByOrders(B11, 0, 2, I3, 0, 0);
			ASSERT1(B11[0] < B11[2]);
			ASSERT1(B11[1] < B11[2]);
			ASSERT1(B11[2] == 3);

			int B12[] = { 3, 2, 1 };
			Partition::PartitionArrayByOrders(B12, 0, 2, I3, 0, 0);
			ASSERT1(B12[0] < B12[2]);
			ASSERT1(B12[1] < B12[2]);
			ASSERT1(B12[2] == 3);

			int B13[6][3] = {
				{ 1, 2, 3 },
				{ 1, 3, 2 },
				{ 2, 1, 3 },
				{ 2, 3, 1 },
				{ 3, 1, 2 },
				{ 3, 2, 1 }
			};

			for (int i = 0; i < 6; i++) {
				Partition::PartitionArrayByOrders(B13[i], 0, 2, I4, 0, 1);
				ASSERT1(B13[i][0] == 1);
				ASSERT1(B13[i][1] == 2);
				ASSERT1(B13[i][2] == 3);
			}

			int B14[6][3] = {
				{ 1, 2, 3 },
				{ 1, 3, 2 },
				{ 2, 1, 3 },
				{ 2, 3, 1 },
				{ 3, 1, 2 },
				{ 3, 2, 1 }
			};

			for (int i = 0; i < 6; i++) {
				Partition::PartitionArrayByOrders(B14[i], 0, 2, I5, 0, 1);
				ASSERT1(B14[i][0] == 1);
				ASSERT1(B14[i][1] == 2);
				ASSERT1(B14[i][2] == 3);
			}

			int B15[6][3] = {
				{ 1, 2, 3 },
				{ 1, 3, 2 },
				{ 2, 1, 3 },
				{ 2, 3, 1 },
				{ 3, 1, 2 },
				{ 3, 2, 1 }
			};

			for (int i = 0; i < 6; i++) {
				Partition::PartitionArrayByOrders(B15[i], 0, 2, I6, 0, 1);
				ASSERT1(B15[i][0] == 1);
				ASSERT1(B15[i][1] == 2);
				ASSERT1(B15[i][2] == 3);
			}

			int B16[6][3] = {
				{ 1, 2, 3 },
				{ 1, 3, 2 },
				{ 2, 1, 3 },
				{ 2, 3, 1 },
				{ 3, 1, 2 },
				{ 3, 2, 1 }
			};

			for (int i = 0; i < 6; i++) {
				Partition::PartitionArrayByOrders(B16[i], 0, 2, I7, 0, 2);
				ASSERT1(B16[i][0] == 1);
				ASSERT1(B16[i][1] == 2);
				ASSERT1(B16[i][2] == 3);
			}
		}
		{
			for (int i = 0; i < 100; i++) {
				int length = 1 + rand();
				int len = 1 + (rand() % (length - 1));

				Logger().WriteInformation("Run %d: %d elements %d indices\n", i, length, len);

				unique_ptr<int[]> input(new int[length]);
				for (int j = 0; j < length; j++) {
					input[j] = rand();
				}

				int delta = length / len;
				unique_ptr<int[]> indices(new int[len]);
				indices[0] = rand() % (delta + 1);
				for (int j = 1; j < len; j++) {
					indices[j] = indices[j - 1] + 1 + (rand() % delta);
				}

				ASSERT1(indices[len - 1] < length);

				Partition::PartitionArrayByOrders((int *)input.get(), 0, length - 1, (int *)indices.get(), 0, len - 1);

				int index = 0;
				for (int j = 0; j < length; j++) {
					if (j == indices[index]) {
						index++;
					}

					if (index < len)
						ASSERT1(input[j] <= input[indices[index]]);

					if (index > 0)
						ASSERT1(input[j] >= input[indices[index - 1]]);
				}
			}
		}
	});

	Add("ByQuantiles", [&]() {
		{
			int A[] = { 1 };
			int I[1];
			Partition::PartitionArrayByQuantiles(A, 1, I, 1);
			ASSERT1(A[0] == 1);
		}
		{
			int A1[] = { 1, 2 };
			int I1[1];
			Partition::PartitionArrayByQuantiles(A1, 2, I1, 2);
			ASSERT1(A1[0] == 1);
			ASSERT1(A1[1] == 2);
			ASSERT1(I1[0] == 1);

			int A2[] = { 2, 1 };
			int I2[1];
			Partition::PartitionArrayByQuantiles(A2, 2, I2, 2);
			ASSERT1(A2[0] == 1);
			ASSERT1(A2[1] == 2);
			ASSERT1(I2[0] == 1);
		}
		{
			int A1[6][3] = {
				{ 1, 2, 3 },
				{ 1, 3, 2 },
				{ 2, 1, 3 },
				{ 2, 3, 1 },
				{ 3, 1, 2 },
				{ 3, 2, 1 }
			};

			for (int i = 0; i < 6; i++) {
				int I[1];
				Partition::PartitionArrayByQuantiles(A1[i], 3, I, 2);
				ASSERT1(A1[i][0] == 1);
				ASSERT1(A1[i][1] == 2);
				ASSERT1(A1[i][2] == 3);
				ASSERT1(I[0] == 1);
			}

			int A2[6][3] = {
				{ 1, 2, 3 },
				{ 1, 3, 2 },
				{ 2, 1, 3 },
				{ 2, 3, 1 },
				{ 3, 1, 2 },
				{ 3, 2, 1 }
			};

			for (int i = 0; i < 6; i++) {
				int I[2];
				Partition::PartitionArrayByQuantiles(A2[i], 3, I, 3);
				ASSERT1(A2[i][0] == 1);
				ASSERT1(A2[i][1] == 2);
				ASSERT1(A2[i][2] == 3);
				ASSERT1(I[0] == 1);
				ASSERT1(I[1] == 2);
			}
		}
		{
			for (int i = 0; i < 100; i++) {
				int length = 1 + rand();
				int len = 1 + (rand() % length);

				Logger().WriteInformation("Run %d: %d elements %d indices\n", i, length, len - 1);

				unique_ptr<int[]> input(new int[length]);
				for (int j = 0; j < length; j++) {
					input[j] = rand();
				}

				unique_ptr<int[]> indices(new int[len - 1]);

				Test::Partition::PartitionArrayByQuantiles((int *)input.get(), length, (int *)indices.get(), len);

				for (int i = 0; i < len - 3; i++) {
					int d1 = indices[i + 1] - indices[i];
					int d2 = indices[i + 2] - indices[i + 1];
					ASSERT1(abs(d1 - d2) <= 1);
				}

				int index = 0;
				for (int j = 0; j < length; j++) {
					if (j == indices[index]) {
						index++;
					}

					if (index < len - 1)
						ASSERT1(input[j] <= input[indices[index]]);

					if (index > 0)
						ASSERT1(input[j] >= input[indices[index - 1]]);
				}
			}
		}
	});
}