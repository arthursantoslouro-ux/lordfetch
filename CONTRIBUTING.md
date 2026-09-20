# Contributing to Lordfetch

**Thank you for your interest in contributing to Lordfetch!**

**Lordfetch is an open-source system information tool written in C. The project is also a way to learn C through practical development, so contributions, ideas, bug reports, and improvements are welcome.**

# Getting Started

**Clone the repository:**

git clone https://github.com/arthursantoslouro-ux/lordfetch.git
cd lordfetch

Build the project:

cmake -S . -B cmake-build
cmake --build cmake-build

Run Lordfetch:

./cmake-build/lordfetch

How to Contribute

You can contribute by:

- Fixing bugs
- Adding support for new Linux distributions
- Improving hardware detection
- Adding new system information
- Improving ASCII logos
- Improving documentation
- Improving compatibility
- Reporting bugs
- Suggesting new features

Adding ASCII Logos

ASCII logos are stored in:

src/logo/ascii/

Logos are organized alphabetically by their name.

For example:

src/logo/ascii/a/arch.txt

After adding or modifying a logo, regenerate the generated logo header:

./scripts/generate_logos.sh

Code Changes

Before submitting a contribution, make sure the project builds successfully:

cmake -S . -B cmake-build
cmake --build cmake-build

Please keep changes focused and avoid unrelated modifications.

Pull Requests

When submitting a pull request:

1. Explain what you changed.
2. Explain why the change is needed.
3. Make sure the project builds successfully.
4. Test the affected functionality.
5. Keep the pull request focused on one change when possible.

Bug Reports

When reporting a bug, please include:

- Operating system
- Distribution
- Architecture
- Steps to reproduce the problem
- Expected behavior
- Actual behavior
- Relevant terminal output

Feature Requests

Feature suggestions are welcome.

Please describe:

- What the feature does
- Why it would be useful
- How you think it could work

License

By contributing to Lordfetch, you agree that your contributions will be licensed under the MIT License.

