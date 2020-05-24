#include "stdafx.h"
#include "CppUnitTest.h"
#include"../CW/Edmonds_Karp_algorithm.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		EdmondsKarp_algorithm test_algorithm;

	public:
		TEST_METHOD(test_input_exception1)
		{
			try
			{
				test_algorithm.input("nonexistent_file.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "File is not found.");
			}
		}
		TEST_METHOD(test_input_exception2)
		{
			try
			{
				test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test1.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "The data in the file is incorrect.");
			}
		}
		TEST_METHOD(test_input_exception3)
		{
			try
			{
				test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test3.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "The data in the file is incorrect.");
			}
		}
		TEST_METHOD(test_input_exception4)
		{
			try
			{
				test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test2.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "A stream coming out of a vertex cannot enter this same vertex.");
			}
		}
		TEST_METHOD(test_input_exception5)
		{
			try
			{
				test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/empty_file.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "The file is empty.");
			}
		}

		TEST_METHOD(test_input_exception6)
		{
			try
			{
				test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test4.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "Input should begin with 'S' and end with 'T'.");
			}
		}

		TEST_METHOD(test_input)
		{
			test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test_right1.txt");
			test_algorithm.~EdmondsKarp_algorithm();
			test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test_right2.txt");
		}

		TEST_METHOD(test_max_flow_exception)
		{
			try
			{
				test_algorithm.max_flow();
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "Data is not set.");
			}
		}

		TEST_METHOD(test_max_flow)
		{
			test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test_right1.txt");
			Assert::AreEqual(test_algorithm.max_flow(), 8);
			test_algorithm.~EdmondsKarp_algorithm();

			test_algorithm.input("C:/Users/Екатерина Иванова/source/repos/CW/CW/test_right2.txt");
			Assert::AreEqual(test_algorithm.max_flow(), 9);
		}
	};
}