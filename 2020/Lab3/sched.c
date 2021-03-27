void sched_yield(void)
{
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    //static int select = 0;
    //static struct Env *pe = NULL;
    struct Env *e = curenv;
    //static int i = 0;
    //static int changed = 0;

        /*
    if(changed){
        changed =0;
        pe=NULL;
    }*/

    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`,
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
        //struct Env *e = curenv;
        while(count == 0 || e == NULL || e->env_status == ENV_NOT_RUNNABLE){
                while(LIST_EMPTY(&env_sched_list[point])){
                        point = 1-point;
                }
                e = LIST_FIRST(&env_sched_list[point]);
                if(e->env_status == ENV_RUNNABLE){
                        count = e->env_pri;
                        LIST_REMOVE(e, env_sched_link);
                        LIST_INSERT_TAIL(&env_sched_list[1-point], e, env_sched_link);
                }
                else if(e->env_status == ENV_FREE){
                        LIST_REMOVE(e, env_sched_link);
                        count = 0;
                        e = NULL;
                }
                else if(e->env_status == ENV_NOT_RUNNABLE){
                        LIST_REMOVE(e, env_sched_link);
                        LIST_INSERT_TAIL(&env_sched_list[1-point], e, env_sched_link);
                        count = 0;
                        e = NULL;
                }
        }
        count--;
        env_run(e);
        /*if(count == 0){
                e = LIST_FIRST(&env_sched_list[point]);
                do{
                        if(LIST_EMPTY(&env_sched_list[point])){
                                point = 1-point;
                        }
                        //e = LIST_FIRST(&env_sched_list[point]);
                                //if(e != NULL){
                        LIST_REMOVE(e, env_sched_link);
                        LIST_INSERT_HEAD(&env_sched_list[1-point], e, env_sched_link);
                        count = e->env_pri;
                                //}
                }while(e == NULL || e->env_status != ENV_RUNNABLE);
        }
        count--;
        env_run(e);*/

        /*if(count == 0){
                e = LIST_FIRST(&env_sched_list[point]);
                do{
                        LIST_REMOVE(e, env_sched_link);
                        LIST_INSERT_TAIL(&env_sched_list[1-point], e, env_sched_link);
                        if(LIST_EMPTY(&env_sched_list[point])){
                                point = 1- point;
                        }
                        e = LIST_FIRST(&env_sched_list[point]);
                        count = e->env_pri;
                }while(e != NULL||e->env_status!=ENV_RUNNABLE);
        }
        count--;
        env_run(e);*/

        /*if (count == 0) {
                env = LIST_FIRST(&env_sched_list[c_list]);
                do {
                        if (env == NULL) {
                        panic("no runnable process\n");
                }
                count = env->env_pri;
                LIST_REMOVE(env, env_sched_link);
                LIST_INSERT_HEAD(&env_sched_list[1 - c_list], env, env_sched_link);
                if (LIST_EMPTY(&env_sched_list[c_list])) {
                        c_list = 1 - c_list;
                }
                } while (env->env_status != ENV_RUNNABLE);
        }
        count--;
        //printf("\n@%d@  ", env->env_pri);
        env_run(env);*/
}