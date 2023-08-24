
#define BUFFLEN (4 * 1024)

const char HEX[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
};

void hex(char *source, char *dest, ssize_t count)
{
  for (ssize_t i = 0; i < count; ++i)
  {
    unsigned char data = source[i];
    dest[2 * i] = HEX[data >> 4];
    dest[2 * i + 1] = HEX[data & 15];
  }
  dest[2 * count] = '\0';
}