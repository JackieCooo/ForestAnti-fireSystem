import {createRouter, createWebHashHistory} from "vue-router";

import LoginPage from "@/components/LoginPage";
import FrontPage from "@/components/FrontPage";
import MainPage from "@/components/MainPage";
import SensorMangePage from "@/components/SensorMangePage";

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
        redirect: '/home/sensor',
        component: MainPage,
        children: [
            {
                path: 'front',
                component: FrontPage,
            },
            {
                path: 'sensor',
                component: SensorMangePage,
            },
        ]
    },
]

const router = createRouter({
    history: createWebHashHistory(),
    routes,
})

export default router;