## The proposal is by Ran Regev (regev.ran@gmail.com) 

#### Links to State Machine Projects:
- Cpp: https://github.com/erikzenker/hsm
- Cpp: https://github.com/boost-ext/sml
- Python: https://github.com/pytransitions/transitions

#### Comments (feel free to add)
- How to define the function on Enter / Exit from and to state
- How to limit the transactions from one state to another? (compile time fail? exception? exit state machine? return error value?)
- What do you do when you move to a state which is forbidden? (same)
- What happens when you get event which can't be handled in this event?
- Possible ways to define CPOs (customization points) for a library: 
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2279r0.html

#### Link to the paper:
https://github.com/wg21il/Papers/tree/P2284/master
