# Setup IDT

- How to define 256 interrupt handlers
- How to install these 256 interrupt handlers to IDT in C function
    - export all symbols of interrupt stub
    - fill the IDT with these symbols
     - how to calculate an selector and offset based on the symbol
    - load idtr with the installed IDT
- How to save the environment before call C function interrupt handler
