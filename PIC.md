# Programmable interrupt controller (PIC)

PIC is an chip that accept the interrupt from the connected hardware devices and feeds the interrupt to CPU. For example, when there is a keyboard hit, the PIC will be signaled via one of its IRQ pins. Then PIC translate the IRQ to a particular system interrupt number and feed it to the CPU. 

However, The default IRQ0-IRQ7 in PIC has a  conflict with the system exception. The IRQ0-IRQ7 in PIC are overlapped by exception 08-10. To fix it, we need to program PIC to remap IRQ0-IRQ7 to other interrupt number.





