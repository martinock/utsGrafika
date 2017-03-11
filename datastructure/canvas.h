#ifndef CANVAS_H
#define CANVAS_H

#include "shape.h"
#include "color.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

#define height 600
#define width_kecil 600
#define width 1280

class Canvas {
	private:
		std::vector<Shape*> bangunan;
		std::vector<Shape*> jalan;
		std::vector<Shape*> pohon;
		std::vector<Shape*> bangunan_besar;
		std::vector<Shape*> jalan_besar;
		std::vector<Shape*> pohon_besar;
		bool p;
		bool b;
		bool j;
		int size_bangunan;
		int size_jalan;
		int size_pohon;
		int size_bangunan_besar;
		int size_jalan_besar;
		int size_pohon_besar;
		void draw_shape(Shape*, const Point&, int, bool);

	public:
		Canvas(std::string, std::string, std::string);
		virtual ~Canvas();
		
		Color IMAGE[width][height];
		std::vector<Shape*> get_all_bangunan() const;
		std::vector<Shape*> get_all_jalan() const;
		std::vector<Shape*> get_all_pohon() const;

		/* Getter */
		Shape* get_bangunan(int) const;
		Shape* get_jalan(int) const;
		Shape* get_pohon(int) const;

		int get_bangunan_size() const;
		int get_jalan_size() const;
		int get_pohon_size() const;

		int get_bangunan_besar_size() const;
		int get_jalan_besar_size() const;
		int get_pohon_besar_size() const;

		void draw_bangunan(int, const Point&, int);
		void draw_jalan(int, const Point&, int);
		void draw_pohon(int, const Point&, int);

		void draw_all_bangunan(const Point&, int);
		void draw_all_jalan(const Point&, int);
		void draw_all_pohon(const Point&, int);

		void draw_all_shapes(const Point&, int);

		void gambarGaris(Point, Point, int, bool);

		void gambarPoint(const Point&, bool);
		bool inside_frame(const Point&, bool);

		void setArg(bool p, bool b, bool j);
		
		void zoom(const Point& Center, double scale);
		void clear_all();

};

#endif
