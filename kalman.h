#include <Eigen/Dense>

#define sigma_x 0.2
#define sigma_v 0.1
#define sigma_zx 0.2
#define sigma_zv 0.1

class filter {
    
    public:     
        Vector2d x_p;
        Vector2d x_k;
        Matrix2d A;
        Vector2d B;
        Matrix2d P_p;
        Matrix2d P_k;
        Matrix2d R;
        Matrix2d I;
        double delta_t = 0.1;

        filter();

        A << 1, delta_t,
            0, 1;

        B << (delta_t * delta_t)/2, delta_t

        P_k << (sigma_x * sigma_x), 0,
                0, (sigma_v * sigma_v);


        P_p << 0, 0,
                0, 0;

        R << (sigma_zx * sigma_zx) , 0,
            0, (sigma_zv * sigma_zv);

        I << 1, 0,
            0, 1;

    
        void predict();

        void update();
}
