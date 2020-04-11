# Papers
A repository for working wg21 papers

## Order
Each paper has its own master branch.
Each paper resides in its own directory.

### Branch Naming
Each paper is prefixed by `P<number>/`
The main paper branch must be called `P<number>/master`.
Working branches on a paper are freely named under `P<number>/<free-name>`
Pull Requests for a paper are naturally go to its master branch.

### Directory Naming
Each paper has its own directory named after the paper name: `P<number>`

### Branch master
The branch `master` contains work that is ready for or was reviewed by WG21.
See [Procedures](https://github.com/wg21il/Papers/wiki/Procedures) for workflow details. 

### Example
The working paper https://wg21.link/p0635 resides in `./P06535` and 
has a master branch `P06535/master`

## Managment
Branches following the `P<number>/master` format are protected from direct commits. Only pull requests are allowed.
`P<number>/master` is enforced by github via: `P[0-9][0-9][0-9][0-9]/master`
