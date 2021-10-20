bool check(int);
void show_plane_inmap(int);
void upd_plane_status(int);
void create_plane();
void rotate(int,int);
bool confirm_plane_put(int);
extern int planemap[16][16],enemymap[16][16];
struct plane{
	int face,x,y,C,number;
};
extern plane plane_list[5];
