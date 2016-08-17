#include <synergy.h>
#include <gtest/gtest.h>

#ifdef _WIN32
	#define CRT_FILE_NAME "ucrtbase.dll"
#elif defined(__linux__)
	#if defined(__i386__)
		#define CRT_FILE_NAME "/usr/lib/libm.so"
	#elif defined(__amd64__)
		#define CRT_FILE_NAME "/usr/lib64/libm.so"
	#endif
#elif defined (__APPLE__)
	#define CRT_FILE_NAME ""
#elif defined (__unix__)
	#define CRT_FILE_NAME ""
#endif

using namespace taylornet::synergy;

struct SynergyTest : testing::Test
{
	NativeLoader* loader;
	NativeLibrary* library;

	SynergyTest()
	{
		this->loader = NativeLoader::getInstance();
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
		library = loader->load(CRT_FILE_NAME);
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
		library = loader->load(CRT_FILE_NAME);
		result = library->call<double>("floor", num);
	}
	catch (std::runtime_error e)
	{
		called = false;
	}

	ASSERT_TRUE(called);
	ASSERT_EQ(result, 10);
}
