import tkinter as tk

def onClick(id):
    btn = list(l.keys())[id]
    if l[btn]:
        btn.configure(bg="orange")
        l[btn] = False
    else:
        btn.configure(bg="red")
        l[btn] = True

def translate():
    if(input_entry.get() == ""):
        input_entry.insert(0, "Becca")
    else:
        l.clear()
        # Maybe use l.key() to remove individual widgets or know when to add widgets instead of resetting each time
        for widget in grid_frame.winfo_children():
            widget.destroy()

        for i in range(3):
            for j in range(0, 8):
                frame = tk.Frame(
                    master=grid_frame,
                    relief=tk.FLAT,
                    borderwidth=1,
                )
                frame.grid(row=i, column=j, padx=2, pady=2)
                data = (i*8) + j
                btn = tk.Button(master=frame, height=5, width=5, bg="orange", command = lambda index=data: onClick(index))
                btn.pack(padx=2, pady=2)
                l[btn] = False
        grid_frame.pack()


window = tk.Tk()

input_frame = tk.Frame(master=window, relief=tk.FLAT)
input_frame.pack(pady=5)

grid_frame = tk.Frame(master=window, relief=tk.FLAT)
grid_frame.pack(pady=5)

submit_frame = tk.Frame(master=window, relief=tk.FLAT)
submit_frame.pack(pady=5)

submit_btn = tk.Button(master=submit_frame, relief=tk.GROOVE, text="Translate", font="Helvetica 14", command=translate)
submit_btn.pack(side=tk.LEFT)

input_label = tk.Label(master=input_frame, text="", font="Helvetica 14")
input_label.pack(side=tk.LEFT)

input_entry = tk.Entry(master=input_frame, font="Helvetica 14", width=10, justify="center")
input_entry.pack(pady=5)


global l
l = {}

for i in range(5):
    for j in range(0, 8):
        frame = tk.Frame(
            master=grid_frame,
            relief=tk.FLAT,
            borderwidth=1,
        )
        frame.grid(row=i, column=j, padx=2, pady=2)
        data = (i*8) + j
        btn = tk.Button(master=frame, height=5, width=5, bg="orange", command = lambda index=data: onClick(index))
        btn.pack(padx=2, pady=2)
        l[btn] = False

window.mainloop()
