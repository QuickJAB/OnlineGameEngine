OnlineGame Project
Setup Instructions
Clone the repository

bash
Copy
Edit
git clone <repository-url>
cd OnlineGame
Run the setup script

On Windows:

cmd
Copy
Edit
setup.bat
On Linux:

bash
Copy
Edit
chmod +x setup.sh
./setup.sh
This will clone and build the external libraries (SDL3, SDL_ttf, ENet) and generate the project files.

Build the projects

On Windows:
Open the generated .sln file in Visual Studio 2022 and build the solution.

On Linux:
Run:

bash
Copy
Edit
make
Notes
Ensure premake5, cmake, Git, and a C++17 compiler are installed and available in your system PATH.

The build targets 64-bit platforms only.

Add source files to Engine/src before building to avoid linker errors.