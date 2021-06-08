# Debug Process - C#

<a href="https://github.com/vltmedia/DebugProcess-Csharp"><img alt="GitHub" src="https://img.shields.io/badge/github-%23121011.svg?style=flat&logo=github&logoColor=white"/></a><img alt="C#" src="https://img.shields.io/badge/c%23-%23239120.svg?style=flat&logo=c-sharp&logoColor=white"/><img alt=".Net" src="https://img.shields.io/badge/.NET-5C2D91?style=flat&logo=.net&logoColor=white"/>

Use this small Console app to debug apps that need to send Arguments to be able to see the arguments and write them out to a file in the same location as this apps exe file.

# Usage

Pass arguments to the ```DebugProcess.exe``` and a new text file in the format of ```DebugProcess_DATETIME.txt``` will be created in the same folder as the .exe file.

```
DebugProcess.exe arg1 arg2 arg3 arg4 arg5
```

## Debug Text Output

A new text file in the format of ```DebugProcess_DATETIME.txt``` will be created in the same folder as the .exe file.

#### Input:

```DebugProcess.exe arg1 argTwo ARG3 ArG_FOUR 5ive six```

#### Output:

```
.--.      .-'.      .--.      .--.      .--.      .--.      .`-.      .--.
:::::.\::::::::.\::::::::.\::::::::.\::::::::.\::::::::.\::::::::.\::::::::.\
'      `--'      `.-'      `--'      `--'      `--'      `-.'      `--'      `


EXE : C:\source\repos\DebugProcess\DebugProcess\bin\Release\DebugProcess.exe
Dir : C:\source\repos\DebugProcess\DebugProcess\bin\Release
Output : C:\source\repos\DebugProcess\DebugProcess\bin\Release\DebugProcess_2021-06-08T015913.txt
DateTime : Tuesday, 08 June 2021 01:59:13
Argument 0 : arg1
Argument 1 : argTwo
Argument 2 : ARG3
Argument 3 : ArG_FOUR
Argument 4 : 5ive
Argument 5 : six


.--.      .-'.      .--.      .--.      .--.      .--.      .`-.      .--.
:::::.\::::::::.\::::::::.\::::::::.\::::::::.\::::::::.\::::::::.\::::::::.\
'      `--'      `.-'      `--'      `--'      `--'      `-.'      `--'      `
```



## Returns

The app will return an ```int``` with a value of ```1``` 

