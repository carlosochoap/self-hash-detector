# Self-Hash Detector

  A C program that reads its own executable bytes and computes its SHA-256 hash using the Windows BCrypt API.

  ## What it does

  1. Locates its own `.exe` path using `GetModuleFileNameA` (Win32 API)
  2. Opens and reads the entire binary into memory (`fopen`, `fread`, `malloc`)
  3. Computes the SHA-256 hash using Windows BCrypt (`BCryptOpenAlgorithmProvider`, `BCryptHashData`, `BCryptFinishHash`)
  4. Prints the hash to the console

  ## Why this matters in malware analysis

  - **Integrity checking**: Malware uses this technique to detect if it has been patched or modified by an antivirus
  - **Self-identification**: Generates a unique ID of the running sample
  - **Anti-tampering**: If the hash changes, the malware knows it has been altered

  ## Techniques covered

  | Concept | Function | C# Equivalent |
  |---------|----------|---------------|
  | Get own path | `GetModuleFileNameA` | `Assembly.GetExecutingAssembly().Location` |
  | Open binary file | `fopen(path, "rb")` | `new FileStream(path, FileMode.Open)` |
  | Get file size | `fseek` + `ftell` | `FileInfo.Length` |
  | Allocate memory | `malloc` | `new byte[]` |
  | Read bytes | `fread` | `stream.Read()` |
  | Compute SHA-256 | `BCryptHashData` | `SHA256.ComputeHash()` |
  | Free memory | `free` | Garbage Collector |

  ## Build

  - **IDE**: Visual Studio 2022+ (Desktop development with C++ workload)
  - **Platform**: Windows (uses Win32 API + BCrypt)
  - **Language**: C (not C++)

  ## Disclaimer

  This project is for **educational and security research purposes only**. The techniques demonstrated are commonly used in malware analysis training and
  defensive security.
