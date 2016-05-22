#include <synergy.h>
#include <gtest\gtest.h>

#ifdef _WIN32
	#define CRT_FILE_NAME "ucrtbase.dll"
#else
	#define CRT_FILE_NAME
#endif

using namespace taylornet::synergy;

struct SynergyTest : testing::Test
{
	loader* loader;
	library* cruntime;

	SynergyTest()
	{
		loader = loader::getInstance();
	}

	virtual ~SynergyTest()
	{
		loader->unloadAll();
		loader = nullptr;
	}
};

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST_F(SynergyTest, CanLoadLibrary)
{
	bool loaded = true;

	try
	{
		
	}
	catch (std::runtime_error e)
	{
		loaded = false;
	}

	ASSERT_TRUE(loaded);
}

TEST_F(SynergyTest, CanCallForiegnSubroutine)
{
	bool called = true;
	double num = 10.9;
	double result;

	try
	{
		cruntime = loader->load(CRT_FILE_NAME);
		result = cruntime->call<double>("floor", num);
	}
	catch (std::runtime_error e)
	{
		called = false;
	}

	ASSERT_TRUE(called);
	ASSERT_EQ(result, 10);
}