#define V2 ImVec2
#define C1 0xA7A830FF
#define C2 0x775839FF

float amp[6], ml;
int pk;

float sqr(float v)
{
    return v * v;
}

void FX(ImDrawList* d, V2 a, V2 b, V2 s, ImVec4 m, float t, V2 pos)
{
    if (m.z > -1)
    {
        if (sqr(m.x - pos.x) + sqr(m.y - pos.y) - sqr(t) <= 2.0f)
            pk = 2;
        else
            pk = 1;
    }
    else
        pk = 1;
    d->AddCircle(pos, t, C1, 0, pk * 2.0f);
}