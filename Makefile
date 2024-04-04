CC := cl
BUILD := build
TRASH := trash
DEFAULT_DEPENDS := kernel32.lib user32.lib shell32.lib gdi32.lib ws2_32.lib

debug:
	$(CC) /c src/networking.cpp
	$(CC) /c src/encryption.cpp
	$(CC) /c src/node.cpp
	$(CC) /c src/serialize.cpp
	$(CC) /c src/utils.cpp

	lib /OUT:$(BUILD)/danlib.lib encryption.obj node.obj serialize.obj utils.obj networking.obj

	$(CC) src/main.cpp /link $(BUILD)/danlib.lib $(DEFAULT_DEPENDS) /OUT:$(BUILD)/test.exe

	rm *.obj