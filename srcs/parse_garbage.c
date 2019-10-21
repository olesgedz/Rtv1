
#include "rtv1.h"
#include "errno.h"

void parse_plane(const cJSON *object, t_game *game)
{
    t_obj *plane;
    t_json parse;

    plane = (t_obj*)malloc(sizeof(t_obj));
    plane->type = PLANE;
    parse.position = cJSON_GetObjectItemCaseSensitive(object, "position");
    parse.x = cJSON_GetArrayItem(parse.position, 0);
    parse.y = cJSON_GetArrayItem(parse.position, 1);
    parse.z = cJSON_GetArrayItem(parse.position, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        plane->position = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        //printf("my start pos: %f,%f,%f\n", x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of plane start pos vector!\n");
    // killer(x, y, z);
    parse.color = cJSON_GetObjectItemCaseSensitive(object, "color");
    parse.x = cJSON_GetArrayItem(parse.color, 0);
    parse.y = cJSON_GetArrayItem(parse.color, 1);
    parse.z = cJSON_GetArrayItem(parse.color, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        plane->color = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of plane color vector!\n");
    // killer(x, y, z);
    parse.v = cJSON_GetObjectItemCaseSensitive(object, "dir");
    parse.x = cJSON_GetArrayItem(parse.v, 0);
    parse.y = cJSON_GetArrayItem(parse.v, 1);
    parse.z = cJSON_GetArrayItem(parse.v, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        plane->v = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of plane dir vector!\n");
    // killer(x, y, z);
    parse.emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (parse.emition != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.emition, 0);
        parse.y = cJSON_GetArrayItem(parse.emition, 1);
        parse.z = cJSON_GetArrayItem(parse.emition, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            plane->emission = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of plane emition vector!\n");
        // killer(x, y, z); 
    }
    else
        plane->emission = create_cfloat3(0.0, 0.0, 0.0);
    parse.reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (parse.reflection != NULL)
        plane->reflection = parse.reflection->valuedouble;
    else
        plane->reflection = 0.0;
    parse.texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (parse.texture != NULL)
        plane->texture = (int)parse.texture->valuedouble;
    else
        plane->texture = 0;
    // cJSON_Delete(position);
    // cJSON_Delete(color);
    // cJSON_Delete(emition);
    // cJSON_Delete(v);
    // cJSON_Delete(reflection);
    // cJSON_Delete(texture);
    // cJSON_Delete(x);
    // cJSON_Delete(y);
    // cJSON_Delete(z);
    ft_object_push(game, plane);
}