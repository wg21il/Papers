# Papers
A repository for working wg21 papers

## Order
Each paper has its own master branch.
Each paper resides in its own directory.

### Branch Naming
Each paper is prefixed by `P<number>/`
The main paper branch must be called `P<number>/master`.
Working branches on a paper are freely named under `P<number>/<free-name>`
Pull Requests for a paper are naturally to its master branch

### Directory Naming
Each paper has its own directory named after the paper name.

### Branch Master
The branch `master` should be empty except for this file.
*No need* to merge `P<number>/master` into master

### Example
The working paper https://wg21.link/p0635 resides in `./P06535` and 
has a master branch `P06535/master`

## Managment
Each paper owner is encouraged to add a restriction not allowing to commit directly to `P<number>/master`
