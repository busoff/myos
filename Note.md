### Why can't receive keyboard interrupt?
I have checked
- remap interrupt in PIC
- write correct value to interrupt bit mask register in PIC
- IDT is setup correctly

and everythin work fine.

And I also observed the IRQ0 always happened once after system startup. As I didn't acknowledge *IRQ0*, thus it only happens once.

Then I acknowledge *IRQ0* each time it happens, this interrupt will happen pericodcally. **What supprise me is the keyboard interrupt comes !!!**

It seems PIC's interrupt is exclusive which means one pending interrupt will block other interrupts until it is acknowledged by CPU.
