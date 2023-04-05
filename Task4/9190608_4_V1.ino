/*
Note that: Before I recorded the video for this task, I didn't know that the user can reprogram the arduino after it is programmed once.
However, I added this feature in the code. You can try it yourself.
I assume that after programming the arduino once then clicking 0, then this is the begining of the new code (excluding the entered 0).
I mean that after clicking the '0' you should write the actual code.
Thanks.
*/



#define rows 4
#define cols 4
char keys[rows][cols] = { {'0', '1', '2', '3'}, {'4', '5', '6', '7'}, {'8', '9', 'A', 'B'}, {'C', 'D', 'E', 'F'} };
const byte rowPins[rows] = {0, 1, 2, 3};
const byte colPins[cols] = {7, 6, 5, 4};



#define max_code_size 150
char code[max_code_size];
bool readCode = false;
int code_size;

int var1;
int var2;
#define output1 8
#define output2 9
#define input1 10
#define input2 11
#define analogInput1 1
#define analogInput2 2

void setup() 
{
  for (int i = 0; i < rows; i++)
  {
    pinMode(rowPins[i], OUTPUT);
  }
  for (int i = 0; i < cols; i++)
  {
    pinMode(colPins[i], INPUT_PULLUP);
  }
  
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
}

void loop() 
{
  if (!readCode)
  {
    read_code(); 
    optimize_code();
  }
   
  for (int i = 0; i < code_size; i += 3)
  {
    if (code[i] == '8')
    {
      for (int j = 0; j < (code[i + 2] - '0'); j++)
      {
        execute(i + 3);
      }
      i += 3;
    }
    else if (code[i] == '5')
    {
      if_function(var1, (code[i + 2] - '0'), i);
      i += 3;
    }
    else if (code[i] == '6')
    {
      if_function(var2, (code[i + 2] - '0'), i);
      i += 3;
    }
    else if (code[i] == '7')
    {
      if_function(var1, var2, i);
      i += 3;
    }
    else
    {
      execute(i);
    }
  }
  char start = get_key();
  if (start == '0')
  {
    readCode = false;
  }
}
char get_key()
{
  for (int i = 0; i < rows; i++)
  {
    digitalWrite(rowPins[i], LOW);
  }
  int pressedCol = -1;
  for (int i = 0; i < cols; i++)
  {
    if (!digitalRead(colPins[i]))
    {
      pressedCol = i;
      break;
    }
  }
  int pressedRow = -1;
  if (pressedCol != -1)
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < rows; j++)
      {
        digitalWrite(rowPins[j], HIGH);
      }
      digitalWrite(rowPins[i], LOW);
      if (!digitalRead(colPins[pressedCol]))
      {
        pressedRow = i;
        break;
      }
    }
  }
  
  if (pressedRow != -1 && pressedCol != -1)
  {
    while (!digitalRead(rowPins[pressedRow]) && !digitalRead(colPins[pressedCol]));
    return keys[pressedRow][pressedCol];
  }
  return 'X';
}

void read_code()
{
  char key = get_key();
  int i = 0;

  while (key != 'F')
  {
    if (key != 'X')
    {
      code[i] = key;
      if (key == 'C')
      {
        int j = 1;
        while(i - j >= 0 && code[i - j] == 'N' || code[i - j] == 'C')
        {
          j++;
        }
        code[i - j] = 'N';
      }
      i++;
    }
    key = get_key();
  }
  code_size = i;
  readCode = true;
}

void optimize_code()
{
  int code_start = -1;
  bool found_zero = false;
  for (int i = 0; i < code_size; i++)
  {
    if (code[i] == 'D')
    {
      code_start = i;
    }
    else if (!found_zero && code[i] == '0' && code_start == -1)
    {
      found_zero = true;
      code_start = i;
    }
  }

  char temp[max_code_size];
  int j = 0;
  for (int i = code_start + 1; i < code_size; i++)
  {
    if (!(code[i] == 'C' || code[i] == 'E' || code[i] == 'N'))
    {
      temp[j] = code[i];
      j++;
    }
  }
  code_size = j;
  for (int i = 0; i < code_size; i++)
  {
    code[i] = temp[i]; 
  }
}

void execute(int i)
{
  switch (code[i])
  {
    case '1':
       if (code[i + 1] == '1')
       {
          var1 += (code[i + 2] - '0');
       }
       else
       {
          var2 += (code[i + 2] - '0');
       }
       break;

    case '2':
       if (code[i + 1] == '1')
       {
          var1 = (code[i + 2] - '0');
       }
       else
       {
          var2 = (code[i + 2] - '0');
       }
       break;

    case '3':
       if (code[i + 1] == '1')
       {
          var1 += var2;
       }
       else
       {
          var2 += var1;
       }
       break;

    case '4':
       if (code[i + 1] == '1')
       {
          var1 = var2;
       }
       else
       {
          var2 = var1;
       }
       break;

    case '9':
      if (code[i + 2] == '1')
      {
        digitalWrite(output1, (code[i + 1] - '0'));
      }
      else
      {
        digitalWrite(output2, (code[i + 1] - '0'));
      }
      break;

     case 'A':
      if (code[i + 1] == '1')
      {
        if (code[i + 2] == '1')
        {
          var1 = digitalRead(input1);
        }
        else
        {
          var1 = digitalRead(input2);
        }
      }
      else
      {
        if (code[i + 2] == '1')
        {
          var2 = digitalRead(input1);
        }
        else
        {
          var2 = digitalRead(input2);
        }
      }
      break;

    case 'B':
      if (code[i + 1] == '1')
      {
        if (code[i + 2] == '1')
        {
          var1 = analogRead(analogInput1);
        }
        else
        {
          var1 = analogRead(analogInput2);
        }
      }
      else
      {
        if (code[i + 2] == '1')
        {
          var2 = analogRead(analogInput1);
        }
        else
        {
          var2 = analogRead(analogInput2);
        }
      }
      break;
  }
}

void if_function(int param1, int param2, int i)
{
  if (code[i + 1] == '1')
  {
    if (param1 > param2)
    {
      execute(i + 3);
    }
  }
  else if (code[i + 1] == '2')
  {
    if (param1 < param2)
    {
      execute(i + 3);
    }
  }
  else
  {
    if (param1 == param2)
    {
      execute(i + 3);
    }
  }
}
