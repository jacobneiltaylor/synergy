#include <synergy.h>
#include <gtest/gtest.h>

#ifdef _WIN32
	#define CRT_FILE_NAME "ucrtbase.dll"
#elif defined(__linux__)
	#if defined(__i386__)
		#define CRT_FILE_NAME "/lib/i386-linux-gnu/libm.so.6"
	#elif defined(__amd64__)
		#define CRT_FILE_NAME "/lib/x86_64-linux-gnu/libm.so.6"
	#endif
#elif defined (__APPLE__)
	#define CRT_FILE_NAME ""
#elif defined (__unix__)
	#define CRT_FILE_NAME ""
#endif

using namespace taylornet::synergy;

struct SynergyTest : testing::Test
{
	loader* libloader;
	library* cruntime;

	SynergyTest()
	{
		this->libloader = loader::getInstance();
	}

	virtual ~SynergyTest()
	{
		libloader->unloadAll();
		libloader = nullptr;
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
		cruntime = libloader->load(CRT_FILE_NAME);
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
		cruntime = libloader->load(CRT_FILE_NAME);
		result = cruntime->call<double>("floor", num);
	}
	catch (std::runtime_error e)
	{
		called = false;
	}

	ASSERT_TRUE(called);
	ASSERT_EQ(result, 10);
}