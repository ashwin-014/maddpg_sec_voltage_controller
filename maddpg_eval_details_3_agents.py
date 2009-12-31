import tensorflow as tf
import gym
from gym import wrappers
import custom_microgrid

from keras.models import load_model

# import make_env
import numpy as np
#import random
#from ReplayMemory import ReplayMemory
from exploration_noise import OrnsteinUhlenbeckActionNoise as OUNoise
from maddpg_model_test_eval import ActorNetwork,CriticNetwork
from maddpg_eval_process_3_agents import eval
import argparse

import logging

logging.basicConfig(level=logging.DEBUG, filename='maddpg.log')

MODEL_SAVE_PATH = "./results/savedmodels/"

def main(args):

    with tf.Session() as sess:
        env = gym.make('Microgrid-beta-v1')
        # env  = make_env.make_env('simple_tag')

        np.random.seed(int(args['random_seed']))
        tf.set_random_seed(int(args['random_seed']))
        env.seed(int(args['random_seed']))

        n = env.n
        actors = []
        critics = []
        exploration_noise = []
        observation_dim = []
        action_dim = []
        total_action_dim = 0
        
        last_epoch = 0

        for i in range(n):
            total_action_dim = total_action_dim + env.action_space[i].n
        for i in range(n):
            observation_dim.append(env.observation_space[i].shape[0])
            
            action_dim.append(env.action_space[i].n) # assuming discrete action space here -> otherwise change to something like env.action_space[i].shape[0]
            actors.append(ActorNetwork(sess,observation_dim[i],action_dim[i],float(args['actor_lr']),float(args['tau'])))
            critics.append(CriticNetwork(sess,n,observation_dim[i],total_action_dim,float(args['actor_lr']),float(args['tau']),float(args['gamma'])))
            mu_init = np.zeros(action_dim[i])
            # mu_init[12]=0.2
            # mu_init[13]=0.3
            # mu_init[14]=0.4
            # mu_init[15]=0.5
            # mu_init[14]=0.4
            # mu_init[13]=0.5
            logging.debug("\naction dim: {0} \nobs dim : {1}".format(action_dim[i], observation_dim[i]))

            mu_init[0]=0.0
            # mu_init[1]=3
            # mu_init[14]=0.9
            exploration_noise.append(OUNoise(mu = mu_init))
        for i in range(n):

            # --------------------- change for num agents ----------

            if bool(args['load_saved']) :
                logging.debug("Now we load the weights of actor and critic: {0}".format(i))
                try:
                    from glob import glob
                    history = list(map(lambda x: int(x.split('-')[1][:-3]), glob(MODEL_SAVE_PATH+'actor'+str(i)+'/mainmodel'+'-*.h5')))
                    logging.debug(history)
                    last_epoch = np.max(history)
                    logging.debug(MODEL_SAVE_PATH + '-'+str(last_epoch)+'.h5')

                    file1 = './results/savedmodels/actor'+str(i)+'/mainmodel-'+str(last_epoch)+'.h5'
                    file2 = './results/savedmodels/actor'+str(i)+'/targetmodel-'+str(last_epoch)+'.h5'
                    file3 = './results/savedmodels/critic'+str(i)+'/mainmodel-'+str(last_epoch)+'.h5'
                    file4 = './results/savedmodels/critic'+str(i)+'/targetmodel-'+str(last_epoch)+'.h5'

                    actors[i].mainModel = load_model(file1)
                    critics[i].mainModel = load_model(file3)
                    actors[i].targetModel = load_model(file2)
                    critics[i].targetModel = load_model(file4)
                    logging.debug("Weight load successfully")
                except:
                    logging.debug("Cannot find the models of actor and critic : {0}".format(i))

            else:
                logging.debug('Training model from scratch\n\n')

        eval(sess,env,args,actors,critics, exploration_noise, last_epoch) #
        #if args['use_gym_monitor']:
        #    envMonitor.monitor.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='provide arguments for DDPG agent')

    # agent parameters
    parser.add_argument('--actor-lr', help='actor network learning rate', default=0.0001)
    parser.add_argument('--critic-lr', help='critic network learning rate', default=0.001)
    parser.add_argument('--gamma', help='discount factor for critic updates', default=0.99)
    parser.add_argument('--tau', help='soft target update parameter', default=0.001)
    parser.add_argument('--buffer-size', help='max size of the replay buffer', default=1000000)
    parser.add_argument('--minibatch-size', help='size of minibatch for minibatch-SGD', default=2) # see change to 32 and 128

    # run parameters
    
    parser.add_argument('--random-seed', help='random seed for repeatability', default=1234)
    parser.add_argument('--max-episodes', help='max num of episodes to do while training', default=10)
    parser.add_argument('--max-episode-len', help='max length of 1 episode', default=1000)
    parser.add_argument('--summary-dir', help='directory for storing tensorboard info', default='./results/tf_ddpg_3')
    parser.add_argument('--load_saved', help='load saved models', default=False, type=bool)

    parser.set_defaults(render_env=False)
    parser.set_defaults(use_gym_monitor=False)

    args = vars(parser.parse_args())

    #pp.pprint(args)

main(args)