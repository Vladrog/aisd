#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication50/rbTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	Assert assert;
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(addRoot)
		{
			rbTree* testTree = new rbTree;
			int key = 4;
			testTree->add(key);
			assert.IsTrue(testTree->contains(key));
			delete testTree;
		}
		TEST_METHOD(addElement)
		{
			rbTree* testTree = new rbTree;
			int key = 4;
			testTree->add(3);
			testTree->add(key);
			assert.IsTrue(testTree->contains(key));
			delete testTree;
		}
		TEST_METHOD(removeElement)
		{
			rbTree* testTree = new rbTree;
			int key = 4;
			testTree->add(key);
			testTree->remove(key);
			assert.IsFalse(testTree->contains(key));
			delete testTree;
		}
		TEST_METHOD(removeNoElement)
		{
			rbTree* testTree = new rbTree;
			bool error = false;
			int key = 4, falseKey = 3;
			testTree->add(falseKey);
			try { testTree->remove(key); }
			catch (logic_error) { error = true; }
			assert.IsTrue(error);
			delete testTree;
		}
		TEST_METHOD(removeEmptyTree)
		{
			rbTree* testTree = new rbTree;
			bool error = false;
			int key = 4;
			try { testTree->remove(key); }
			catch (logic_error) { error = true; }
			assert.IsTrue(error);
			delete testTree;
		}
		TEST_METHOD(contains)
		{
			rbTree* testTree = new rbTree;
			int key = 4, falseKey = 3;
			testTree->add(key);
			assert.IsTrue(testTree->contains(key) && !testTree->contains(falseKey));
			delete testTree;
		}
	};
}
