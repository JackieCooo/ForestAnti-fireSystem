import {createRouter, createWebHashHistory} from "vue-router";

import LoginPage from "@/components/LoginPage";
import FrontPage from "@/components/FrontPage";
import MainPage from "@/components/MainPage";

const routes = [
    {
        path: '/',
        redirect: '/home',
    },
    {
        path: '/login',
        component: LoginPage,
    },
    {
        path: '/home',
        redirect: '/home/front',
        component: MainPage,
        children: [
            {
                path: 'front',
                component: FrontPage,
            },
        ]
    },
]

const router = createRouter({
    history: createWebHashHistory(),
    routes,
})

export default router;