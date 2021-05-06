from pyglet.gl import *
import ShaderLoader
from ObjLoader import ObjLoader
from pyrr import Vector3, matrix44, Matrix44
import time
import numpy


class Cube:
    def __init__(self):
        mesh = ObjLoader()
        mesh.load_model("../models/cube.obj")
        self.num_verts = len(mesh.vertex_index)
        cube_texture_offset = len(mesh.vertex_index) * 12
        cube_data = numpy.array(mesh.model, dtype=GLfloat)

        self.vao_cube = GLuint()
        # generate a vertex array object for the cube - the vao
        glGenVertexArrays(1, self.vao_cube)
        # bind the cube's vao
        glBindVertexArray(self.vao_cube)
        # setup the cube's vertex buffer object - the vbo
        vbo_sphere = pyglet.graphics.vertexbuffer.create_buffer(cube_data.nbytes, GL_ARRAY_BUFFER, GL_STATIC_DRAW)
        vbo_sphere.bind()
        vbo_sphere.set_data(cube_data.ctypes.data)

        # vertex attribute pointer settings for the cube vbo
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0)
        glEnableVertexAttribArray(0)
        # textures
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, cube_texture_offset)
        glEnableVertexAttribArray(1)

        glBindBuffer(GL_ARRAY_BUFFER, 0)  # unbind the vbo
        glBindVertexArray(0)  # unbind the vao

        # region texture settings
        self.texture = GLuint(0)
        glGenTextures(1, self.texture)
        glBindTexture(GL_TEXTURE_2D, self.texture)
        # set the texture wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
        # set the texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

        image = pyglet.image.load('../models/cube.jpg')
        image_data = image.get_data('RGB', image.pitch)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data)
        # endregion

    def render(self):
        # to draw the cube, we need to rebind the cube's vao
        glBindVertexArray(self.vao_cube)
        glBindTexture(GL_TEXTURE_2D, self.texture)
        glUniformMatrix4fv(InitShader.model_loc, 1, GL_FALSE, InitShader.c_cube_model)
        glDrawArrays(GL_TRIANGLES, 0, self.num_verts)
        glBindVertexArray(0)


class Monkey:
    def __init__(self):
        mesh = ObjLoader()
        mesh.load_model("../models/monkey.obj")
        self.num_verts = len(mesh.vertex_index)
        monkey_texture_offset = len(mesh.vertex_index) * 12
        monkey_data = numpy.array(mesh.model, dtype=GLfloat)

        self.vao_monkey = GLuint()
        # generate a vertex array object for the monkey - the vao
        glGenVertexArrays(1, self.vao_monkey)
        # bind the monkey's vao
        glBindVertexArray(self.vao_monkey)
        # setup the monkey's vertex buffer object - the vbo
        monkey_vbo = pyglet.graphics.vertexbuffer.create_buffer(monkey_data.nbytes, GL_ARRAY_BUFFER, GL_STATIC_DRAW)
        monkey_vbo.bind()
        monkey_vbo.set_data(monkey_data.ctypes.data)

        # vertex attribute pointer settings for the monkey vbo
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0)
        glEnableVertexAttribArray(0)
        # textures
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, monkey_texture_offset)
        glEnableVertexAttribArray(1)

        glBindBuffer(GL_ARRAY_BUFFER, 0)  # unbind the vbo
        glBindVertexArray(0)  # unbind the vao

        # region texture settings
        self.texture = GLuint(0)
        glGenTextures(1, self.texture)
        glBindTexture(GL_TEXTURE_2D, self.texture)
        # set the texture wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
        # set the texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

        image = pyglet.image.load('../models/monkey.jpg')
        image_data = image.get_data('RGB', image.pitch)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data)
        # endregion

    def render(self):
        # creating a rotation matrix for the monkey
        ct = time.clock()
        rot_y = Matrix44.from_y_rotation(ct*0.5)
        rot_y = matrix44.multiply(rot_y, InitShader.monkey_model).flatten().astype("float32")
        c_rotate = numpy.ctypeslib.as_ctypes(rot_y)

        # to draw the monkey, we need to rebind the monkey's vao
        glBindVertexArray(self.vao_monkey)
        glBindTexture(GL_TEXTURE_2D, self.texture)
        glUniformMatrix4fv(InitShader.model_loc, 1, GL_FALSE, c_rotate)
        glDrawArrays(GL_TRIANGLES, 0, self.num_verts)
        glBindVertexArray(0)


class InitShader:
    shader = None
    model_loc = None
    monkey_model = None
    cube_model = None
    c_cube_model = None

    @staticmethod
    def init():
        InitShader.create_shader()
        InitShader.create_perspective_projection()
        InitShader.create_translations()

    @staticmethod
    def create_shader():
        InitShader.shader = ShaderLoader.compile_shader("shaders/video_14_vert.glsl", "shaders/video_14_frag.glsl")
        glUseProgram(InitShader.shader)

    @staticmethod
    def create_perspective_projection():
        view = matrix44.create_from_translation(Vector3([0.0, 0.0, -2.0]))
        projection = matrix44.create_perspective_projection_matrix(45.0, 1280.0 / 720.0, 0.1, 100.0)
        vp = matrix44.multiply(view, projection).flatten().astype("float32")
        c_vp = numpy.ctypeslib.as_ctypes(vp)
        vp_loc = glGetUniformLocation(InitShader.shader, b"vp")
        glUniformMatrix4fv(vp_loc, 1, GL_FALSE, c_vp)

    @staticmethod
    def create_translations():
        InitShader.model_loc = glGetUniformLocation(InitShader.shader, b"model")
        # translation for the monkey, flattening on the second line because the rotation
        InitShader.monkey_model = matrix44.create_from_translation(Vector3([-2.0, 0.0, -3.0]))
        # translation for the cube
        InitShader.cube_model = matrix44.create_from_translation(Vector3([2.0, 0.0, -3.0])).flatten().astype("float32")
        InitShader.c_cube_model = numpy.ctypeslib.as_ctypes(InitShader.cube_model)


class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.set_minimum_size(400, 300)
        glClearColor(0.0, 0.0, 0.0, 1.0)
        glEnable(GL_DEPTH_TEST)

        InitShader.init()
        self.monkey = Monkey()
        self.cube = Cube()

    def on_draw(self):
        self.clear()
        self.monkey.render()
        self.cube.render()

    def on_resize(self, width, height):
        glViewport(0, 0, width, height)

    def update(self, dt):
        pass


if __name__ == "__main__":
    window = MyWindow(1280, 720, "My Pyglet Window", resizable=True)
    pyglet.clock.schedule_interval(window.update, 1/60.0)
    pyglet.app.run()
