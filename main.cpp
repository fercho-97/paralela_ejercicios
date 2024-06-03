#include <iostream>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <omp.h>

#define WIDTH 1920
#define HEIGHT 1080

#define PALET_SIZE 16
int max_iteraciones = 100;


const double x_min = -2;
const double x_max = 1;

const double y_min = -1;
const double y_max = 1;


static unsigned int *pixel_buffer = nullptr;

uint32_t _bswap(uint32_t a) {

    return
            ((a & 0X000000FF) << 24) |
            ((a & 0X0000FF00) << 8) |
            ((a & 0X00FF0000) >> 8) |
            ((a & 0XFF000000) >> 24);
}

std::vector<unsigned int> color_ramp = {

        _bswap(0xFF1010FF),
        _bswap(0xEF1019FF),
        _bswap(0xE01123FF),
        _bswap(0xD1112DFF),
        _bswap(0xC11237FF),
        _bswap(0xB21341FF),
        _bswap(0xA3134BFF),
        _bswap(0x931455FF),
        _bswap(0x84145EFF),
        _bswap(0x751568FF),
        _bswap(0x651672FF),
        _bswap(0x56167CFF),
        _bswap(0x471786FF),
        _bswap(0x371790FF),
        _bswap(0x28189AFF),
        _bswap(0x1919A4FF)


};

enum class runtime_type_enum {
    rtCPU,
    rtOpenMP,
    rtOpenMPManual
};

static runtime_type_enum runtime_type = runtime_type_enum::rtCPU;

unsigned int divergente(double cx, double cy) {
    int iter = 0;
    double vx = cx;
    double vy = cy;
    while (iter < max_iteraciones && (vx * vx + vy * vy) <= 4) {
        //Zn+1=Zn^2+C
        double tx = vx * vx - vy * vy + cx; //vx"2 - vy"2+cx
        double ty = 2 * vx * vy + cy;  // 2vx vy +cy

        vx = tx;
        vy = ty;

        iter++;
    }
//    if((vx*vx+vy*vy)>4){
//        return 0xFF00FFFF ;
//    }

    if (iter > 0 && iter < max_iteraciones) {
        //diverge
        //return 0x000FFFF;

        int color_idx = iter % PALET_SIZE;

        return color_ramp[color_idx];

    } else {
        //convergente
        return 0xFFFFFFF;

    }
}

void mandelbrotCpu() {

    double dx = (x_max - x_min) / WIDTH;
    double dy = (y_max - y_min) / HEIGHT;


    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double x = x_min + i * dx;
            double y = y_max - j * dy;

            //C=X+Yi
            unsigned int color = divergente(x, y);
            pixel_buffer[j * WIDTH + i] = color;
        }
    }
}

void mandelbrotOpenMP() {

    double dx = (x_max - x_min) / WIDTH;
    double dy = (y_max - y_min) / HEIGHT;

#pragma omp parallel for default(none) shared(dx, dy, pixel_buffer) num_threads(48)


    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double x = x_min + i * dx;
            double y = y_max - j * dy;

            //C=X+Yi
            unsigned int color = divergente(x, y);
            pixel_buffer[j * WIDTH + i] = color;
        }
    }
}

void mandelbrotOpenMPManual() {
    double dx = (x_max - x_min) / WIDTH;
    double dy = (y_max - y_min) / HEIGHT;

    int num_threads = omp_get_max_threads();
    int rows_threads = HEIGHT / num_threads;


#pragma omp parallel default(none) shared(dx, dy, pixel_buffer, num_threads, rows_threads)
    {

        int thread_id = omp_get_thread_num();

        int start_row = thread_id * rows_threads;
        int end_row = (thread_id == num_threads - 1) ? HEIGHT : start_row + rows_threads;

        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                double x = x_min + i * dx;
                double y = y_max - j * dy;

                //C=X+Yi
                unsigned int color = divergente(x, y);
                pixel_buffer[j * WIDTH + i] = color;
            }
        }
    }

}

int main() {
    int num_threads = 0;
#pragma omp parallel  default(none) shared(num_threads)
    {
#pragma omp master
        {
            num_threads = omp_get_num_threads();
            fmt::println("num_threads: {}", num_threads);
        }
    }


    sf::Text text;
    sf::Font font;

    {
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString("Ejemplo OpenMP");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setPosition(450, 100);
    }
    sf::Text textOptions;
    {
        textOptions.setFont(font);
        textOptions.setString("OPTIONS: [1]CPU [2]OMP [3]OMPManual [4]MoreIteration+100 [5]LessIteration-100");
        textOptions.setCharacterSize(24);
        textOptions.setFillColor(sf::Color::White);
        textOptions.setStyle(sf::Text::Bold);

    }



    //CREACION DE TEXTURA
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);


    //GENERAR SPRITE
    sf::Sprite sprite;
    sprite.setTexture(texture);

    pixel_buffer = new unsigned int[WIDTH * HEIGHT];

    //ESCRIBIR LA IMAGEN EN EL DISCO
    // sf::Image img;
    //  img.create(WIDTH,HEIGHT,(const sf::Uint8*) pixel_buffer);
    //  img.saveToFile("c:/conan-2.3.0-windows-x86_64/imagen1.jpg");;
    //para ver lo de forma grafica


    auto window = sf::RenderWindow{{WIDTH, HEIGHT}, "CMake SFML Project"};
    window.setFramerateLimit(144);

    sf::Clock clock;
    int frames = 0;
    int fps = 0;

    textOptions.setPosition(10, window.getView().getSize().y - 40);
    while (window.isOpen()) {
        //for (auto event = sf::Event{}; window.pollEvent(event);)
        sf::Event event;
        while (window.pollEvent(event)) {
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::Resized) {
                    textOptions.setPosition(10, window.getView().getSize().y - 40);

                } else if (event.type == sf::Event::KeyReleased) {
                    switch (event.key.scancode) {
                        case sf::Keyboard::Scan::Num1:
                            //cpu
                            runtime_type = runtime_type_enum::rtCPU;
                            break;
                        case sf::Keyboard::Scan::Num2:
                            //openmp
                            runtime_type = runtime_type_enum::rtOpenMP;
                            break;

                        case sf::Keyboard::Scan::Num3:
                            runtime_type = runtime_type_enum::rtOpenMPManual;

                            break;
                        case sf::Keyboard::Scan::Num4:
                            max_iteraciones += 100;

                            break;

                        case sf::Keyboard::Scan::Num5:
                            max_iteraciones -= 100;

                            break;
                    }
                }
            }
        }


        if (runtime_type == runtime_type_enum::rtCPU) {
            mandelbrotCpu();
        } else {
            mandelbrotOpenMP();

        }


        texture.update((const sf::Uint8 *) pixel_buffer);
        //formatear el texto
        auto msg = fmt::format("MANDELBROT SET: Mode={}, iterations:{}, FPS: {} ,CORES:{}",
                               (runtime_type == runtime_type_enum::rtCPU ? "CPU" :
                                (runtime_type == runtime_type_enum::rtOpenMP ? "OpenMP" : "OpenMPManual")),
                                        max_iteraciones, fps, num_threads);

        text.setString(msg);


        if (clock.getElapsedTime().asSeconds() >= 1.0) {
            fps = frames;
            frames = 0;
            clock.restart();
        }
        frames++;

        window.clear();
        {
            window.draw(sprite);

            window.draw(text);
            window.draw(textOptions);


        }
        window.display();


    }
    delete[] pixel_buffer;
}