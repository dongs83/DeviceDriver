#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TS, TC1) {
	
	MockFlashMemoryDevice mock;
	DeviceDriver driver { &mock };

	EXPECT_CALL(mock, read(_))
		.Times(5)
		.WillRepeatedly(Return((int)0xAA));
	
	int result = driver.read(0xA);
}
TEST(TS, TC2) {
	
	MockFlashMemoryDevice mockHW;
	DeviceDriver dd{ &mockHW };

	EXPECT_CALL(mockHW, read((long)0xA))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDA));

	EXPECT_THROW(dd.read(0xA), std::exception);
}
TEST(TS, TC4) {
	NiceMock<MockFlashMemoryDevice> mockHW;
	DeviceDriver dd{ &mockHW };

	EXPECT_CALL(mockHW, read((long)0xA))
		.Times(1)
		.WillOnce(Return(0xFA));

	EXPECT_THROW(dd.write((long)0xA, 0x33),
		std::exception);
}

TEST(TS, TC3) {
	NiceMock<MockFlashMemoryDevice> mockHW;
	DeviceDriver dd{ &mockHW };

	EXPECT_CALL(mockHW, read((long)0xA))
		.Times(1)
		.WillOnce(Return(0xFF));

	dd.write((long)0xA, 0x33);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}