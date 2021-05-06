from pyglet.gl import *
import ShaderLoader


class Triangle:
    def __init__(self):
        self.verts = pyglet.graphics.vertex_list(3, ('v3f', (-0.5,-0.5,0.0, 0.5,-0.5,0.0, 0.0,0.5,0.0)),
                                                    ('c3f', ( 1.0, 0.0,0.0, 0.0, 1.0,0.0, 0.0,0.0,1.0)))

        shader = ShaderLoader.compile_shader("shaders/video_11_vert.glsl", "shaders/video_11_frag.glsl")

        glUseProgram(shader)

        # vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, self.verts.vertices)
        glEnableVertexAttribArray(0)

        # colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, self.verts.colors)
        glEnableVertexAttribArray(1)



class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.set_minimum_size(400, 300)
        glClearColor(0.2, 0.3, 0.2, 1.0)

        self.triangle = Triangle()

    def on_draw(self):
        self.clear()
        self.triangle.verts.draw(GL_TRIANGLES)

    def on_resize(self, width, height):
        glViewport(0, 0, width, height)

    def update(self, dt):
        pass


if __name__ == "__main__":
    window = MyWindow(1280, 720, "My Pyglet Window", resizable=True)
    pyglet.clock.schedule_interval(window.update, 1/60.0)
    pyglet.app.run()
