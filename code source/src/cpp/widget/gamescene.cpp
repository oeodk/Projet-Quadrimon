#include "widget/GameScene.h"
#include <fstream>
#include <sstream>
#include <QOpenGLContext>
#include <QApplication>
#include <QScreen>

static constexpr float ANGLE = 40;
static constexpr float DISTANCE = 24.5;

GameScene::GameScene(QWidget* parent)
	: QOpenGLWidget(parent)
{
    internal_counter_ = 0;
    center_position_.set(0.0f, 0.f, 2.5f);
    POV_ = false;
}

void GameScene::updateScene()
{
    constexpr float ROTATION_FRAME_COUNT = 3000;
    view_.setToIdentity();
    if (!POV_)
    {
        center_position_.set(0.0f, 0.f, 2.5f);
        camera_position_.set((DISTANCE * cos((ANGLE / 180.f) * M_PI)) * cos(internal_counter_ * (2 * M_PI) / ROTATION_FRAME_COUNT), (DISTANCE * cos((ANGLE / 180.f) * M_PI)) * sin(internal_counter_ * (2 * M_PI) / ROTATION_FRAME_COUNT), DISTANCE * sin((ANGLE / 180.f) * M_PI));
    }
    view_.lookAt(camera_position_, center_position_, QVector3D(0.0f, 0.f, 1.0f));
    internal_counter_++;
}

void GameScene::initializeGL()
{
    // Recovering openGL functions
	initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Loading main shader
    loadShader(main_shader_program_, "./assets/shaders/vertex_base_shader.glsl", "./assets/shaders/fragment_base_shader.glsl");

    // Initializing camera ans projection matrix

    light_position_ = bdm::Vector3f(0.f, 0.f, 10.f);
    camera_position_ = bdm::Vector3f(DISTANCE * cos((ANGLE / 108.f) * M_PI), 0.f, DISTANCE * sin((ANGLE / 108.f) * M_PI));
    view_.lookAt(camera_position_, QVector3D(0.0f, 0.f, 2.5f), QVector3D(0.0f,0.f, 1.0f));
    projection_.setToIdentity();
    projection_.perspective(45.0f, width() / float(height()), 0.1f, 100);

    // Initializing uniforms
    main_uniforms_location_.insert({ "projection_view", 0 });
    main_uniforms_location_.at("projection_view") = glGetUniformLocation(main_shader_program_, "projection_view");
    main_uniforms_location_.insert({ "model", 0 });
    main_uniforms_location_.at("model") = glGetUniformLocation(main_shader_program_, "model");

    main_uniforms_location_.insert({ "material.ambient", 0 });
    main_uniforms_location_.at("material.ambient") = glGetUniformLocation(main_shader_program_, "material.ambient");
    main_uniforms_location_.insert({ "material.diffuse", 0 });
    main_uniforms_location_.at("material.diffuse") = glGetUniformLocation(main_shader_program_, "material.diffuse");
    main_uniforms_location_.insert({ "material.specular", 0 });
    main_uniforms_location_.at("material.specular") = glGetUniformLocation(main_shader_program_, "material.specular");
    main_uniforms_location_.insert({ "material.shininess", 0 });
    main_uniforms_location_.at("material.shininess") = glGetUniformLocation(main_shader_program_, "material.shininess");

    main_uniforms_location_.insert({ "light_position", 0 });
    main_uniforms_location_.at("light_position") = glGetUniformLocation(main_shader_program_, "light_position");
    main_uniforms_location_.insert({ "cam_pos", 0 });
    main_uniforms_location_.at("cam_pos") = glGetUniformLocation(main_shader_program_, "cam_pos");
    main_uniforms_location_.insert({ "object_color", 0 });
    main_uniforms_location_.at("object_color") = glGetUniformLocation(main_shader_program_, "object_color");
    main_uniforms_location_.insert({ "textureSampler",0 });

    main_uniforms_location_.at("textureSampler") = glGetUniformLocation(main_shader_program_, "textureSampler");
    main_uniforms_location_.insert({ "secondTextureSampler",0 });
    main_uniforms_location_.at("secondTextureSampler") = glGetUniformLocation(main_shader_program_, "secondTextureSampler");

    main_uniforms_location_.insert({ "has_texture",0 });
    main_uniforms_location_.at("has_texture") = glGetUniformLocation(main_shader_program_, "has_texture");
    main_uniforms_location_.insert({ "has_second_texture",0 });
    main_uniforms_location_.at("has_second_texture") = glGetUniformLocation(main_shader_program_, "has_second_texture");
    main_uniforms_location_.insert({ "blend_factor",0 });
    main_uniforms_location_.at("blend_factor") = glGetUniformLocation(main_shader_program_, "blend_factor");

    main_uniforms_location_.insert({ "shadowMap",0 });
    main_uniforms_location_.at("shadowMap") = glGetUniformLocation(main_shader_program_, "shadowMap");
    main_uniforms_location_.insert({ "light_projection",0 });
    main_uniforms_location_.at("light_projection") = glGetUniformLocation(main_shader_program_, "light_projection");
    
    

    // Initialization of the main framebuffer
    const int SCREEN_WIDTH = width() * 2, SCREEN_HEIGHT = height() * 2;
    width_ = SCREEN_WIDTH;
    height_ = SCREEN_HEIGHT;
    glGenFramebuffers(1, &main_fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, main_fbo_);
   
    glGenTextures(1, &main_texture_);
    glBindTexture(GL_TEXTURE_2D, main_texture_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, main_texture_, 0);
    
    glGenRenderbuffers(1, &main_rbo_);
    glBindRenderbuffer(GL_RENDERBUFFER, main_rbo_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, main_rbo_);

    auto fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fbo_status != GL_FRAMEBUFFER_COMPLETE)
    {
        qDebug() << fbo_status;
    }
    glGenVertexArrays(1, &rectangle_vao_);
    glBindVertexArray(rectangle_vao_);

    glGenBuffers(1, &rectangle_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, rectangle_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(display_rectangle_), &display_rectangle_, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    loadShader(display_shader_program_, "./assets/shaders/vertex_display.glsl", "./assets/shaders/fragment_display.glsl");
    glUseProgram(display_shader_program_);
    glUniform1i(glGetUniformLocation(display_shader_program_, "screenTexture"), 0);
    glUniform1i(glGetUniformLocation(display_shader_program_, "bloomTexture"), 1);
    main_uniforms_location_.insert({ "gamma",0 });
    glUniform1f(glGetUniformLocation(display_shader_program_, "gamma"), GAMMA_);
    glUseProgram(0);

    // gaussian bloom initialization
    glBindFramebuffer(GL_FRAMEBUFFER, main_fbo_);
    glGenTextures(1, &bloom_texture_);
    glBindTexture(GL_TEXTURE_2D, bloom_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bloom_texture_, 0);
    attachment_[0] = GL_COLOR_ATTACHMENT0;
    attachment_[1] = GL_COLOR_ATTACHMENT1;
    glDrawBuffers(2, attachment_);

    // CoDAW bloom initialization
    loadShader(bloom_shader_program_, "./assets/shaders/vertex_display.glsl", "./assets/shaders/fragment_bloom_CoDAW.glsl");
    bloom_uniforms_location_.insert({ "screenTexture",0 });
    bloom_uniforms_location_.at("screenTexture") = glGetUniformLocation(bloom_shader_program_, "screenTexture");
    bloom_uniforms_location_.insert({ "downscale",0 });
    bloom_uniforms_location_.at("downscale") = glGetUniformLocation(bloom_shader_program_, "downscale");
    bloom_uniforms_location_.insert({ "srcResolution",0 });
    bloom_uniforms_location_.at("srcResolution") = glGetUniformLocation(bloom_shader_program_, "srcResolution");
    bloom_uniforms_location_.insert({ "filterRadius",0 });
    bloom_uniforms_location_.at("filterRadius") = glGetUniformLocation(bloom_shader_program_, "filterRadius");
    glGenFramebuffers(1, &bloom_fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, bloom_fbo_);
    bdm::Vector2f mip_size(SCREEN_WIDTH, SCREEN_HEIGHT);
    bdm::Vector2f mip_int_size(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int i = 0; i < bloom_mips_.size(); i++)
    {
        mip_size *= 0.5f;
        mip_int_size.set(static_cast<int>(mip_int_size.x * 0.5), static_cast<int>(mip_int_size.y * 0.5));
        bloom_mips_[i].size.set(mip_size);
        bloom_mips_[i].int_size.set(mip_int_size);

        glGenTextures(1, &bloom_mips_[i].texture);
        glBindTexture(GL_TEXTURE_2D, bloom_mips_[i].texture);
        // we are downscaling an HDR color buffer, so we need a float texture format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, (int)mip_size.x, (int)mip_size.y, 0, GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloom_mips_[0].texture, 0);
    glDrawBuffers(1, attachments_bloom_);
    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("gbuffer FBO error, status: 0x\%x\n", status);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //initialization of shadow map elements
    glGenFramebuffers(1, &shadow_map_fbo_);
    glGenTextures(1, &shadow_map_text_);
    glBindTexture(GL_TEXTURE_2D, shadow_map_text_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_MAP_WIDTH_, SHADOW_MAP_HEIGHT_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clamp_color_);

    glBindFramebuffer(GL_FRAMEBUFFER, shadow_map_fbo_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_map_text_, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    const float ortho_value = 35;
    orthogonal_projection_.ortho(-ortho_value, ortho_value, -ortho_value, ortho_value, 0.1, 300);
    light_view_.lookAt(light_position_ * 5.f, QVector3D(0, 0, 0), QVector3D(0.0f, 1.f, 0.0f));
    light_projection_ = orthogonal_projection_ * light_view_;

    loadShader(shadow_shader_program_, "./assets/shaders/vertex_shadow.glsl", "./assets/shaders/fragment_shadow.glsl");
    shadow_uniforms_location_.insert({ "light_projection", 0 });
    shadow_uniforms_location_.at("light_projection") = glGetUniformLocation(shadow_shader_program_, "light_projection");
    shadow_uniforms_location_.insert({ "model", 0 });
    shadow_uniforms_location_.at("model") = glGetUniformLocation(shadow_shader_program_, "model");
    
    glUseProgram(shadow_shader_program_);
    glUniformMatrix4fv(shadow_uniforms_location_.at("light_projection"), 1, GL_FALSE, light_projection_.data());
    glUseProgram(0);

    loadShader(overlay_shader_program_, "./assets/shaders/vertex_overlay.glsl", "./assets/shaders/fragment_overlay.glsl");
    overlay_uniforms_location_.insert({ "model", 0 });
    overlay_uniforms_location_.at("model") = glGetUniformLocation(overlay_shader_program_, "model");
    overlay_uniforms_location_.insert({ "textureSampler", 0 });
    overlay_uniforms_location_.at("textureSampler") = glGetUniformLocation(overlay_shader_program_, "textureSampler");
    overlay_uniforms_location_.insert({ "object_color", 0 });
    overlay_uniforms_location_.at("object_color") = glGetUniformLocation(overlay_shader_program_, "object_color");

    QMatrix4x4 overlay_view, overlay_projection, projection_view;
    overlay_view.lookAt(QVector3D(0, 0, 2), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    overlay_projection.ortho(-1, 1, -1, 1, -1, 1);
    projection_view = overlay_projection * overlay_view;
    glUseProgram(overlay_shader_program_);
    glUniformMatrix4fv(glGetUniformLocation(overlay_shader_program_, "projection_view"), 1, GL_FALSE, projection_view_.data());
    glUseProgram(0);

    glLineWidth(2);
    glPointSize(2);

    // Calling the slot for initializing the game
    emit initGlFinished();
}

void GameScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawShadow();
    drawPolygons();
    drawOnScreen();

    auto err = glGetError();
    if (err != GL_NONE)
    {
        qDebug() << err;
    }
}

float GameScene::getScreenScaleFactor() 
{
    // Get the primary screen
    QWidget* window = QApplication::activeWindow();
    if (!window) {
        return 1.0; // Default scale factor
    }
    QScreen* screen = window->screen();
    if (!screen) {
        return 1.0; // Default scale factor
    }

    // Get the device pixel ratio
    qreal devicePixelRatio = screen->devicePixelRatio();

    // Get the logical DPI
    qreal logicalDpi = screen->logicalDotsPerInch();

    // Calculate the scale factor
    float scaleFactor = devicePixelRatio * logicalDpi / 96.0; // Assuming 96 DPI is the standard

    return scaleFactor;
}

void GameScene::drawPolygons()
{
    // Combining the view and projection matrix to reduce the GPU calculs
    glBindFramebuffer(GL_FRAMEBUFFER, main_fbo_);
    glViewport(0, 0, width_, height_);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    projection_view_ = projection_ * view_;
    glUseProgram(main_shader_program_);
    // Sending common uniforms
    glUniform3fv(main_uniforms_location_.at("light_position"), 1, light_position_.data());
    glUniform3fv(main_uniforms_location_.at("cam_pos"), 1, camera_position_.data());
    glUniformMatrix4fv(main_uniforms_location_.at("projection_view"), 1, GL_FALSE, projection_view_.data());
    // Drawing every polygons
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadow_map_text_);
    glUniform1i(main_uniforms_location_.at("shadowMap"), 0);
    glUniformMatrix4fv(main_uniforms_location_.at("light_projection"), 1, GL_FALSE, light_projection_.data());

    glActiveTexture(GL_TEXTURE1);

    for (auto& polygon : polygons_)
    {
        polygon->bind();
        QMatrix4x4 polygon_model(polygon->getCombineModel());
        glUniformMatrix4fv(main_uniforms_location_.at("model"), 1, GL_FALSE, polygon_model.data());

        glUniform3fv(main_uniforms_location_.at("material.ambient"), 1, polygon->material_.ambient.data());
        glUniform3fv(main_uniforms_location_.at("material.diffuse"), 1, polygon->material_.diffuse.data());
        glUniform3fv(main_uniforms_location_.at("material.specular"), 1, polygon->material_.specular.data());
        glUniform1f(main_uniforms_location_.at("material.shininess"), polygon->material_.shininess);

        glUniform4fv(main_uniforms_location_.at("object_color"), 1, polygon->color_.data());
        glUniform1i(main_uniforms_location_.at("textureSampler"), 1);
        glUniform1i(main_uniforms_location_.at("has_texture"), polygon->has_texture_);
        if (dynamic_cast<BiTextureOpenGlPolygon*>(polygon))
        {
            BiTextureOpenGlPolygon* biTexturePolygon = dynamic_cast<BiTextureOpenGlPolygon*>(polygon);
            glActiveTexture(GL_TEXTURE2);
            biTexturePolygon->bindSecondTexture();
            glUniform1i(main_uniforms_location_.at("secondTextureSampler"), 2);
            glUniform1i(main_uniforms_location_.at("has_second_texture"), biTexturePolygon->has_second_texture_);
            glUniform1f(main_uniforms_location_.at("blend_factor"), biTexturePolygon->blend_factor_);
            glActiveTexture(GL_TEXTURE1);
        }
        else
        {
            glUniform1i(main_uniforms_location_.at("has_second_texture"), false);
        }


        glDrawElements(polygon->opengl_primitive_, polygon->indices_.size(), GL_UNSIGNED_INT, 0);
        polygon->release();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glUseProgram(0);
}

void GameScene::drawShadow()
{
    glUseProgram(shadow_shader_program_);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, SHADOW_MAP_WIDTH_, SHADOW_MAP_HEIGHT_);
    glBindFramebuffer(GL_FRAMEBUFFER, shadow_map_fbo_);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(shadow_uniforms_location_.at("light_projection"), 1, GL_FALSE, light_projection_.data());

    for (auto& shadow_polygon: shadow_polygons_)
    {
        shadow_polygon->bind();
        QMatrix4x4 polygon_model(shadow_polygon->getCombineModel());
        glUniformMatrix4fv(shadow_uniforms_location_.at("model"), 1, GL_FALSE, polygon_model.data());
        glDrawElements(shadow_polygon->opengl_primitive_, shadow_polygon->indices_.size(), GL_UNSIGNED_INT, 0);
        shadow_polygon->release();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glUseProgram(0); 
}

void GameScene::drawOnScreen()
{
    glUseProgram(bloom_shader_program_);
    glBindFramebuffer(GL_FRAMEBUFFER, bloom_fbo_);
    bool downscale = true;
    glUniform1i(bloom_uniforms_location_.at("downscale"), downscale);
    glUniform1f(bloom_uniforms_location_.at("filterRadius"), 0);
    glUniform2f(bloom_uniforms_location_.at("srcResolution"), width_, height_);
    glUniform1f(bloom_uniforms_location_.at("filterRadius"), 0.005f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bloom_texture_);
    for (int i = 0; i < bloom_mips_.size(); i++)
    {
        const BloomMip& mip = bloom_mips_[i];
        glViewport(0, 0, mip.size.x, mip.size.y);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip.texture, 0);
        // Render screen-filled quad of resolution of current mip
        glBindVertexArray(rectangle_vao_);
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6); 
        glBindVertexArray(0);
        // Set current mip resolution as srcResolution for next iteration
        glUniform2f(bloom_uniforms_location_.at("srcResolution"), mip.size.x, mip.size.y);
        // Set current mip as texture input for next iteration
        glBindTexture(GL_TEXTURE_2D, mip.texture);
    }
    
    downscale = false;
    glUniform1i(bloom_uniforms_location_.at("downscale"), downscale);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_FUNC_ADD);

    for (int i = bloom_mips_.size() - 1; i > 0; i--)
    {
        const BloomMip& mip = bloom_mips_[i];
        const BloomMip& nextMip = bloom_mips_[i - 1];

        // Bind viewport and texture from where to read
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mip.texture);

        // Set framebuffer render target (we write to this texture)
        glViewport(0, 0, nextMip.size.x, nextMip.size.y);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, nextMip.texture, 0);

        // Render screen-filled quad of resolution of current mip
        glBindVertexArray(rectangle_vao_);
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    const float scale_factor = getScreenScaleFactor();
    glViewport(0, 0, scale_factor * width(), scale_factor * height());

    glUseProgram(display_shader_program_);
    glDisable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, main_texture_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bloom_mips_[0].texture);
    glBindVertexArray(rectangle_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(overlay_shader_program_);
    glActiveTexture(GL_TEXTURE1);

    for (auto& polygon : overlay_polygons_)
    {
        polygon->bind();
        QMatrix4x4 polygon_model(polygon->getCombineModel());
        glUniformMatrix4fv(overlay_uniforms_location_.at("model"), 1, GL_FALSE, polygon_model.data());
        glUniform1i(overlay_uniforms_location_.at("textureSampler"), 1);
        glUniform4fv(overlay_uniforms_location_.at("object_color"), 1, polygon->color_.data());

        glDrawElements(polygon->opengl_primitive_, polygon->indices_.size(), GL_UNSIGNED_INT, 0);
        polygon->release();
    }
    glUseProgram(0);
}

std::string GameScene::loadShaderSource(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        qDebug() << "Could not open the file: " + filename + '\n';
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void GameScene::loadShader(unsigned int& program, const std::string& vertex_shader_path, const std::string& frag_shader_path)
{
    GLint success, vertexShader, fragmentShader;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertexShaderSource = loadShaderSource(vertex_shader_path);
    const char* vs = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qDebug() << "Vertex Shader Compilation Failed:" << infoLog;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string fragmentShaderSource = loadShaderSource(frag_shader_path);
    const char* fs = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        qDebug() << "frag Shader Compilation Failed:" << infoLog;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        qDebug() << "Shader Program Linking Failed:" << infoLog;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(0);
}

