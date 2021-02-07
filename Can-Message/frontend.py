import subprocess
import tkinter as tk
import os


def onClick(id):
    btn = list(l.keys())[id]
    if l[btn]:
        btn.configure(bg="orange")
        l[btn] = False
    else:
        btn.configure(bg="red")
        l[btn] = True

def translate():
    word = input_entry.get()
    if word != "":
        rows = len(word)

        l.clear()
        # Maybe use l.key() to remove individual widgets or know when to add widgets instead of resetting each time
        for widget in grid_frame.winfo_children():
            widget.destroy()

        dirname = os.path.dirname(__file__)
        filename = os.path.join(dirname, 'cmake-build-debug')
        f = open("input.txt", "w")
        f.write("W\n")
        f.write(word)
        f.close()
        command = r"cd " + filename
        os.chdir(filename)
        os.system("Can_Message")
        os.chdir(filename + r"\..")
        f = open("output.txt", "r")

        matrix_string = f.readline()

        for i in range(rows):
            for j in range(0, 8):
                frame = tk.Frame(
                    master=grid_frame,
                    relief=tk.FLAT,
                    borderwidth=1,
                )
                frame.grid(row=i, column=j, padx=2, pady=2)
                data = (i*8) + j
                value = matrix_string[data] == "1"
                btn = tk.Button(master=frame, height=5, width=5, bg="red" if value else "orange", command=lambda index=data: onClick(index))
                btn.pack(padx=2, pady=2)
                l[btn] = matrix_string[data] == "1"
        # grid_frame.pack()
    else:
        f = open("input.txt", "w")
        f.write("M\n")

        grid_children = grid_frame.winfo_children()
        row = int(len(grid_children)/8)
        f.write(f"{row}\n")
        for children in grid_frame.winfo_children():
            value = l[children.winfo_children()[0]]
            if value:
                f.write("1")
            else:
                f.write("0")
        f.close()

        dirname = os.path.dirname(__file__)
        filename = os.path.join(dirname, 'cmake-build-debug')
        command = r"cd " + filename
        os.chdir(filename)
        os.system("Can_Message")
        os.chdir(filename + r"\..")
        f = open("output.txt", "r")

        output = f.readline()
        input_entry.insert(0, output)


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
