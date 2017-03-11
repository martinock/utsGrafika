#include "canvas.h"

void read_file_bangunan(std::vector<Shape*>& bangunan, std::vector<Shape*>& bangunan_besar, std::string file_bangunan){
	freopen(file_bangunan.c_str(), "r", stdin);
	// Remove the old S
	for(int i = 0;i < (int)bangunan.size(); ++i){
		delete bangunan[i];
	}	
	for(int i = 0;i < (int)bangunan_besar.size(); ++i){
		delete bangunan_besar[i];
	}
	bangunan.clear();
	bangunan_besar.clear();
	int n;
	while(scanf("%d", &n) != EOF){
		Shape *Sh = new Shape(n + 1);

		Shape *Sh_besar = new Shape(n+1);

		for(int i = 0;i < n; ++i){
			int x, y;
			scanf("%d%d", &x, &y);
			Point P = Point(x, y);
			Point P_besar = Point(x+640, y);
			Sh->setPoint(i, P);
			Sh_besar->setPoint(i, P_besar);
		}
		Point P = Sh->getPoint(0);
		Sh->setPoint(n, P);

		Point P_besar = Sh_besar->getPoint(0);
		Sh_besar->setPoint(n, P_besar);

		bangunan.push_back(Sh);
		bangunan_besar.push_back(Sh_besar);
	}
	fclose(stdin);
}

void read_file_jalan(std::vector<Shape*>& jalan, std::vector<Shape*>& jalan_besar, std::string file_jalan){
	freopen(file_jalan.c_str(), "r", stdin);
	// Remove the old S
	for(int i = 0;i < (int)jalan.size(); ++i){
		delete jalan[i];
	}
	for(int i = 0;i < (int)jalan_besar.size(); ++i){
		delete jalan_besar[i];
	}
	jalan.clear();
	jalan_besar.clear();
	int n;
	while(scanf("%d", &n) != EOF){
		Shape *Sh = new Shape(n);
		Shape *Sh_besar = new Shape(n);
		for(int i = 0;i < n; ++i){
			int x, y;
			scanf("%d%d", &x, &y);
			Point P = Point(x*137/100, y*137/100);
			Point P_besar = Point((x*137/100)+640, y*137/100);
			Sh->setPoint(i, P);
			Sh_besar->setPoint(i, P_besar);
		}
		jalan.push_back(Sh);
		jalan_besar.push_back(Sh_besar);
	}
	fclose(stdin);
}

void read_file_pohon(std::vector<Shape*>& pohon, std::vector<Shape*>& pohon_besar, std::string file_pohon){
	freopen(file_pohon.c_str(), "r", stdin);
	// Remove the old S
	for(int i = 0;i < (int)pohon.size(); ++i){
		delete pohon[i];
	}
	for(int i = 0;i < (int)pohon_besar.size(); ++i){
		delete pohon_besar[i];
	}
	pohon.clear();
	pohon_besar.clear();
	int n;
	while(scanf("%d", &n) != EOF){
		for(int i = 0;i < n; ++i){

			int total_titik = 3;
			int x, y;
			scanf("%d%d", &x, &y);
			Point pusat = Point(x * 137 / 100, y * 137 / 100);
			Point pusat_besar = Point((x * 137 / 100)+640, y * 137 / 100);
			Shape *Sh = new Shape(total_titik + 1);
			Shape *Sh_besar = new Shape(total_titik + 1);
			for(int j = 0;j < total_titik; ++j){
				Point P = Point(pusat);
				Point P_besar = Point(pusat_besar);
				switch(j){
					case 0: 
						P.setY(P.getY() - 2); 
						P_besar.setY(P_besar.getY() - 2);
						break;
					case 1: 
						P.setX(P.getX() - 2); 
						P_besar.setX(P_besar.getX() - 2);
						break;
					case 2: 
						P.setX(P.getX() + 2); 
						P_besar.setX(P_besar.getX() + 2); 
						break;
				}
				Sh->setPoint(j, P);
				Sh_besar->setPoint(j, P_besar);
			}
			Sh->setPoint(total_titik, Sh->getPoint(0));
			Sh_besar->setPoint(total_titik, Sh_besar->getPoint(0));
			
			pohon.push_back(Sh);
			pohon_besar.push_back(Sh_besar);
		}
	}
	fclose(stdin);
}

Canvas::Canvas(std::string file_bangunan, std::string file_jalan, std::string file_pohon) {
	read_file_bangunan(bangunan, bangunan_besar, file_bangunan);
	read_file_jalan(jalan, jalan_besar, file_jalan);
	read_file_pohon(pohon, pohon_besar, file_pohon);
	size_bangunan = bangunan.size();
	size_jalan = jalan.size();
	size_pohon = pohon.size();
	size_bangunan_besar = bangunan_besar.size();

	size_jalan_besar = jalan_besar.size();
	size_pohon_besar = pohon_besar.size();
}

Canvas::~Canvas() {
	for(int i = 0;i < size_bangunan; ++i){
		delete bangunan[i];
	}
	bangunan.clear();

	for(int i = 0;i < size_jalan; ++i){
		delete jalan[i];
	}
	jalan.clear();

	for(int i = 0;i < size_pohon; ++i){
		delete pohon[i];
	}
	pohon.clear();
}

std::vector<Shape*> Canvas::get_all_bangunan() const {
	return bangunan;
}

std::vector<Shape*> Canvas::get_all_jalan() const {
	return jalan;
}

std::vector<Shape*> Canvas::get_all_pohon() const {
	return pohon;
}

Shape* Canvas::get_bangunan(int idx) const{
	return bangunan[idx];
}
Shape* Canvas::get_jalan(int idx) const{
	return jalan[idx];
}
Shape* Canvas::get_pohon(int idx) const{
	return pohon[idx];
}	

int Canvas::get_bangunan_size() const{
	return size_bangunan;
}
int Canvas::get_jalan_size() const{
	return size_jalan;
}
int Canvas::get_pohon_size() const{
	return size_pohon;
}

int Canvas::get_bangunan_besar_size() const{
	return size_bangunan_besar;
}
int Canvas::get_jalan_besar_size() const{
	return size_jalan_besar;
}
int Canvas::get_pohon_besar_size() const{
	return size_pohon_besar;
}

void Canvas::draw_shape(Shape *S, const Point& P, int scale, bool zoomed){
	int num_titik = S->getSize();
	for(int i = 0;i < num_titik - 1; ++i){
		gambarGaris((S->getPoint(i)).scaleUp(P, scale), (S->getPoint(i+1)).scaleUp(P, scale), scale-1, zoomed);
	}
}

void Canvas::draw_bangunan(int idx, const Point& P, int scale){
	draw_shape(bangunan[idx], P, scale, 1);
	draw_shape(bangunan_besar[idx], P, 1, 0);
}

void Canvas::draw_jalan(int idx, const Point& P, int scale){
	draw_shape(jalan[idx], P, scale, 1);
	draw_shape(jalan_besar[idx], P, 1, 0);	
}

void Canvas::draw_pohon(int idx, const Point& P, int scale){
	draw_shape(pohon[idx], P, scale, 1);
	draw_shape(pohon_besar[idx], P, 1, 0);
}

void Canvas::draw_all_bangunan(const Point& P, int scale){
	for(int i = 0;i < get_bangunan_size(); ++i) draw_bangunan(i, P, scale);
}
void Canvas::draw_all_jalan(const Point& P, int scale){
	for(int i = 0;i < get_jalan_size(); ++i) draw_jalan(i, P, scale);
}
void Canvas::draw_all_pohon(const Point& P, int scale){
	for(int i = 0;i < get_pohon_size(); ++i) draw_pohon(i, P, scale);
}

void Canvas::draw_all_shapes(const Point& P, int scale) {
	if (b){
		draw_all_bangunan(P, scale);
	}
	if (p) {
		draw_all_pohon(P, scale);
	}
	if (j) {
		draw_all_jalan(P, scale);
	}
}

void Canvas::gambarGaris(Point P1, Point P2, int tebal, bool zoomed) {
	for(int t1 = -tebal; t1 <= tebal; ++t1){
		for(int t2 = -tebal; t2 <= tebal; ++t2){
			int xawal = P1.getX() < P2.getX() ? P1.getX() : P2.getX();
			int xakhir = P2.getX() > P1.getX() ? P2.getX() : P1.getX();

			int yawal = P1.getY(), yakhir = P2.getY();
			if(xawal != P1.getX()){
				std::swap(yawal, yakhir);
			}

			xawal += t1;
			xakhir += t1;
			yawal += t2;
			yakhir += t2;

			int selisihAbsX = xawal - xakhir >= 0 ? xawal - xakhir : xakhir - xawal;
			int selisihAbsY = yawal - yakhir >= 0 ? yawal - yakhir : yakhir - yawal;

			//bagi kasus kalo selisihnya 0
			if(selisihAbsX == 0){
				if(yawal > yakhir) std::swap(yawal, yakhir);
				for(int i = yawal; i <= yakhir; ++i){
					Point P = Point(xawal, i);
					gambarPoint(P, zoomed);
				}
			}
			else if (selisihAbsY == 0){
				if(xawal > xakhir) std::swap(xawal, xakhir);
				for(int i = xawal; i <= xakhir; ++i){
					Point P = Point(i, yawal);
					gambarPoint(P, zoomed);
				}
			}
			else if(selisihAbsY < selisihAbsX){
				if(xawal > xakhir) std::swap(xawal, xakhir), std::swap(yawal, yakhir);
				int deltaY = yakhir - yawal;
				int deltaX = xakhir - xawal;
				for(int i = 0; i <= deltaX; ++i){
					int modY = (deltaY * i) % deltaX;
					int ynow = yawal + (deltaY * i) / deltaX + (modY * 2) / deltaX;

					Point P = Point(xawal + i, ynow);
					gambarPoint(P, zoomed);
				}
			}
			else{
				if(yawal > yakhir) std::swap(xawal, xakhir), std::swap(yawal, yakhir);
				int deltaY = yakhir - yawal;
				int deltaX = xakhir - xawal;
				for(int i = 0; i <= deltaY; ++i){
					int modX = (deltaX * i) % deltaY;
					int xnow = xawal + (deltaX * i) / deltaY + (modX * 2) / deltaY;

					Point P = Point(xnow, yawal + i);
					gambarPoint(P, zoomed);
				}
			}

		}
	}
}

void Canvas::gambarPoint(const Point& P, bool zoomed){
	if (inside_frame(P, zoomed)){
		IMAGE[P.getX()][P.getY()] = Color(0, 0, 200);
	}
}

bool Canvas::inside_frame(const Point& P, bool zoomed){
	if(zoomed) return P.getX() < width_kecil && P.getY() < height && P.getX() >= 0 && P.getY() >= 0;
	else return P.getX() < width && P.getY() < height && P.getX() >= 0 && P.getY() >= 0;
}

void Canvas::zoom(const Point& Center, double scale){
	for(int i = 0;i < (int)bangunan.size(); ++i){
		Point *points = bangunan[i]->getAllPoint();
		int p_size = bangunan[i]->getSize();
		for(int j = 0;j < p_size; ++j){
			points[j].scaleUp(Center,scale);
		}
	}
	for(int i = 0;i < (int)jalan.size(); ++i){
		Point *points = jalan[i]->getAllPoint();
		int p_size = jalan[i]->getSize();
		for(int j = 0;j < p_size; ++j){
			points[j].scaleUp(Center,scale);
		}
	}
	for(int i = 0;i < (int)pohon.size(); ++i){
		Point *points = pohon[i]->getAllPoint();
		int p_size = pohon[i]->getSize();
		for(int j = 0;j < p_size; ++j){
			points[j].scaleUp(Center,scale);
		}
	}
}

void Canvas::setArg(bool p, bool b, bool j){
	this->p = p;
	this->b = b;
	this->j = j;
}

void Canvas::clear_all(){
	for(int i = 0;i < width; ++i){
		for(int j = 0;j < height; ++j){
			IMAGE[i][j] = Color(0,0,0);
		}
	}
}
