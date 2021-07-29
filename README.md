# aDLL - Adventure of Dinamic Lynk Library

_aDLL is a binary analysis tool focused on the automatic discovery of DLL Hijacking vulnerabilities. The tool analyzes the image of the binary loaded in memory to search for DLLs loaded at load-time and makes use of the Microsoft Detours library to intercept calls to the LoadLibrary/LoadLibraryEx functions to analyze the DLLs loaded at run-time. The purpose is to obtain a list of DLLs that are not found by the executable in those folders where they are searched._

## Getting Started 

_To start using aDLL a compiled executable is available in the Binaries folder. It is recommended to use the version whose architecture (32-bit or 64-bit) matches the version of the executable to be analyzed._

_For the correct functioning of the tool, it is necessary that the DLLs "hook32", "hook64", "informer32" and "informer64" are located in the same directory as the executable aDLL.exe._
### Prerequisites 

_aDLL has been developed and tested on Windows 10 systems._
_If the system is old and/or Visual Studio is not installed, it is possible that the tool will throw an error like "VCRUNTIME140.dll not found". In this case the Visual C++ Redistributable update must be installed.
 Update can be found here: https://www.microsoft.com/es-ES/download/details.aspx?id=49984._

### Compilation 

_To modify/recompile the tool it is recommended the use of Visual Studio 2015 or later._
_The Visual Studio solution consists of three projects: aDLL, Hook e Informer.
    -aDLL: must be compiled as an executable. If linking errors occur, it will be necessary to add the shlwapi.lib library using the Visual Studio linker as an additional dependency.
    -Hook: must be compiled as a DLL with the same architecture as the executable to be analyzed. The resulting Hook file must be renamed to hook32.dll or hook64.dll as appropriate. If you wish to analyze executables of both architectures it will be necessary to have both DLLs in the same directory as aDLL.exe. 
    -Informer: same as Hook. Must be compiled as a DLL and renamed to informer32.dll or informer64.dll.
_

## Usage ⚙️

_The tool has a -h option to print a brief description of the available options on the screen.._
```
.\aDLL -h
```
_As a common example of usage aDLL should receive at least the path to the executable to be analyzed._
```
.\aDLL -e "C:\System32\notepad.exe"
```
_OPTIONS:_

```
-h Displays the tool's help with a brief description of each option.
-e Specifies the path to the executable to be analyzed by aDLL.
-t Specifies a path to a text file with a list of executable paths.
-o Specifies a path to a directory in which a report will be stored for each executable scanned.
-m Searches for the executable's manifest and displays it on the screen. aDLL searches for the manifest embedded in the binary, it will not find the manifest if it exists as an external file.
-w Defines the number of seconds the executable process will be kept open while searching for DLLs loaded at runtime. The default time is 20 seconds.
-aDLL will automatically test if a malicious DLL is executed by impersonating the legitimate DLL in the search order if a candidate DLL has been found.
-d Used in conjunction with the -a option, this option allows you to select a path to a DLL that will be used as the malicious DLL.
-r Each DLL imported by the executable can in turn import other DLLs as dependencies. A search "n" times recursive will be made on all those DLLs found by aDLL that are not redirected (ApiSetSchema or WinSxS) and do not belong to the list of Known DLL of the system.
```
## Acknowledgments

_Hook DLL is based on the idea of ctxis's DLLHSC: https://github.com/ctxis/DLLHSC_

## Contact

_ideaslocas@telefonica.com_# aDLL

you can find more information about licenses at: licenses.txt

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
WHENEVER YOU MAKE A CONTRIBUTION TO A REPOSITORY CONTAINING NOTICE OF A LICENSE, 
YOU LICENSE YOUR CONTRIBUTION UNDER THE SAME TERMS, AND YOU AGREE 
THAT YOU HAVE THE RIGHT TO LICENSE YOUR CONTRIBUTION UNDER THOSE TERMS. 
IF YOU HAVE A SEPARATE AGREEMENT TO LICENSE YOUR CONTRIBUTIONS UNDER DIFFERENT TERMS, 
SUCH AS A CONTRIBUTOR LICENSE AGREEMENT, THAT AGREEMENT WILL SUPERSEDE.
