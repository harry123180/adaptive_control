from pyglet.gl import *
from Triangle3 import Triangle

class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.set_minimum_size(400, 300)
        glClearColor(0.2, 0.3, 0.2, 1.0)

        self.triangle = Triangle()


    def on_draw(self):
        self.clear()
        glDrawArrays(GL_TRIANGLES, 0, 3)

    def on_resize(self, width, height):
        glViewport(0, 0, width, height)

    def update(self, dt):
        self.triangle.rotate()


if __name__ == "__main__":
    window = MyWindow(1280, 720, "My Pyglet Window", resizable=True)
    pyglet.clock.schedule_interval(window.update, 1/30.0)
    pyglet.app.run()
